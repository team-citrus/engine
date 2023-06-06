/*
*   name: src/jobs.rs
*   origin: Citrus Engine
*   purpose: The Job system and public interface
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{thread, sync::{atomic::*, Mutex}, vec::Vec, collections::VecDeque, boxed::Box, mem::drop};
use rand::thread_rng;

static thread_count: AtomicI32;
static max_thread_count: AtomicI32;
static jobs_queued: Mutex<VecDeque<JobTuple>>;
static engine_jobs_queued: Mutex<VecDeque<JobTuple>>;
static jobs_executing: Mutex<Vec<JobTuple>>;

pub trait Job {
    fn execute(mut self) -> ();
    fn job_id(&self) -> u64;
}

#[derive(Copy, Clone, Eq, PartialEq)]
pub struct JobHandle {
    id: u64,
}

struct JobTuple(u64, Box<dyn Job>);

pub fn schedule<T: Job + Clone>(job: &T) -> JobHandle {
    let tmp = JobHandle { id: thread_rng().next_u64() & (~(1 << 63)), };
    let tuple = JobTuple(tmp.id, Box::new(*job));

    match jobs_queued.lock() {
        Ok(guard) => { guard.deref_mut().push_back(tuple) },
        Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
    }

    refresh_job_system();
    tmp
}

pub(crate) fn engine_schedule<T: Job + Clone>(job: &T) -> JobHandle {
    let tmp = JobHandle { id: thread_rng().next_u64() | (1 << 63), };
    let tuple = JobTuple(tmp.id, Box::new(*job));

    match engine_jobs_queued.lock() {
        Ok(guard) => { guard.deref_mut().push_back(tuple) },
        Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
    }

    refresh_job_system();
    tmp
}

fn job_system_thread() -> () {
    loop {
        let mut outages = 0;
        match engine_jobs_queued.lock() {
            Ok(guard) => {
                if guard.deref().len() == 0 {
                    outages += 1;
                } else {
                    let mut job = guard.deref_mut().pop_front().unwrap();
                    let idx;
                    match jobs_executing.lock() {
                        Ok(inner) => {
                            idx = inner.deref().len();

                            inner.deref_mut().push(job);
                        },
                        Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
                    }
                    drop(guard);
                    *(job.1).execute();
                    continue;
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        }

        match jobs_queued.lock() {
            Ok(guard) => {
                if guard.deref().len() == 0 {
                    outages += 1;
                } else {
                    let mut job = guard.deref_mut().pop_front().unwrap();
                    let idx;
                    match jobs_executing.lock() {
                        Ok(inner) => {
                            idx = inner.deref().len();
                            inner.deref_mut().push(job);
                        },
                        Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
                    }
                    drop(guard);
                    *(job.1).execute();
                    continue;
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        }

        if outages == 2 break;
    }

    thread_count.fetch_sub(1, Ordering::SeqCst);
}

fn refresh_job_system() -> () {
    loop {
        let mut outages = 0;
        match engine_jobs_queued.lock() {
            Ok(guard) => { 
                let _cmp = thread_count.load(Ordering::SeqCst) < max_thread_count.load(Ordering::SeqCst);

                if guard.deref().len() != 0 && _cmp {
                    thread_count.fetch_sub(1, Ordering::SeqCst);
                    thread::Builder::new().name("Job System Thread".to_string()).spawn(|| job_system_thread());
                    drop(guard);
                } else if _cmp == false {
                    break;
                } else {
                    outages += 1;
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        }
        match jobs_queued.lock() {
            Ok(guard) => { 
                let _cmp = thread_count.load(Ordering::SeqCst) < max_thread_count.load(Ordering::SeqCst);

                if guard.deref().len() != 0 && _cmp {
                    thread_count.fetch_sub(1, Ordering::SeqCst);
                    thread::Builder::new().name("Job System Thread".to_string()).spawn(|| job_system_thread());
                    drop(guard);
                } else if _cmp == false {
                    break;
                } else {
                    outages += 1;
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        }

        if outages == 2 { break; }
    }
}

impl JobHandle {
    pub fn complete(&self) -> i32 {
        // TODO: this
        1
    }
}