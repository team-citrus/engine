/*
*   name: src/jobs.rs
*   origin: Citrus ENGINE
*   purpose: The Job system and public interface
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{thread, sync::{atomic::*, Mutex, BarrierWaitResult}, vec::Vec, collections::VecDeque, boxed::Box, mem::drop, ops::{Deref, DerefMut}};
use rand::thread_rng;
use lazy_static::lazy_static;
use num_cpus;

use crate::internal::gameplay::waste_cpu_cycles;

const COMPLETE_BLOCK_FOR: u8 = 255; // At 2.8ghz, this will block for a little over 10 milliseconds

// TODO: Improve power efficiency
// TODO: Rework pretty much all of the complete related code.

lazy_static! {
    static ref THREAD_COUNT: AtomicI32 = AtomicI32::new(0);
    static ref MAX_THREAD_COUNT: AtomicI32 = AtomicI32::new(num_cpus::get() * 2);
    static ref JOBS_QUEUED: Mutex<VecDeque<JobTuple>> = Mutex::new(VecDeque::with_capacity(num_cpus::get() * 2));
    static ref ENGINE_JOBS_QUEUED: Mutex<VecDeque<JobTuple>> = Mutex::new(VecDeque::with_capacity(num_cpus::get() * 2));
    static ref JOBS_EXECUTING: Mutex<Vec<JobTuple>> = Mutex::new(VecDeque::with_capacity(num_cpus::get() * 2));
}

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
    let tmp = JobHandle { id: thread_rng().next_u64() & (!(1 << 63)), };
    let tuple = JobTuple(tmp.id, Box::new(*job));

    match JOBS_QUEUED.lock() {
        Ok(guard) => { guard.deref_mut().push_back(tuple) },
        Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
    }

    refresh_job_system();
    tmp
}

pub(crate) fn engine_schedule<T: Job + Clone>(job: &T) -> JobHandle {
    let tmp = JobHandle { id: thread_rng().next_u64() | (1 << 63), };
    let tuple = JobTuple(tmp.id, Box::new(*job));

    match ENGINE_JOBS_QUEUED.deref().lock() {
        Ok(guard) => { guard.deref_mut().push_back(tuple) },
        Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
    }

    refresh_job_system();
    tmp
}

fn job_system_thread() -> () {
    loop {
        let mut outages = 0;
        match ENGINE_JOBS_QUEUED.deref().lock() {
            Ok(mut guard) => {
                if guard.deref().len() == 0 {
                    outages += 1;
                } else {
                    let mut job = guard.deref_mut().pop_front().unwrap();
                    let idx;

                    match JOBS_EXECUTING.lock() {
                        Ok(mut inner) => {
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

        match JOBS_QUEUED.deref().lock() {
            Ok(mut guard) => {
                if guard.deref().len() == 0 {
                    outages += 1;
                } else {
                    let mut job = guard.deref_mut().pop_front().unwrap();
                    let idx;

                    match JOBS_EXECUTING.lock() {
                        Ok(mut inner) => {
                            idx = inner.deref().len();
                            inner.deref_mut().push(job);
                        },
                        Err(err) => {
                            panic!("A catastrophic jobsystem error has occured. {}", err)
                        },
                    }

                    drop(guard);
                    *(job.1).execute();

                    continue;
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        }

        if outages >= 2 && outages <= 6 {
            thread::yield_now()
        } else if outages > 6 {
            break;
        }
    }

    THREAD_COUNT.deref().fetch_sub(1, Ordering::SeqCst);
}

fn refresh_job_system() -> () {
    loop {
        let mut outages = 0;

        match ENGINE_JOBS_QUEUED.deref().lock() {
            Ok(guard) => {
                let _cmp = THREAD_COUNT.deref().load(Ordering::SeqCst) < MAX_THREAD_COUNT.deref().load(Ordering::SeqCst);

                if guard.deref().len() != 0 && _cmp {
                    THREAD_COUNT.deref().fetch_add(1, Ordering::SeqCst);
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

        match JOBS_QUEUED.deref().lock() {
            Ok(guard) => {
                let _cmp = THREAD_COUNT.deref().load(Ordering::SeqCst) < MAX_THREAD_COUNT.deref().load(Ordering::SeqCst);

                if guard.deref().len() != 0 && _cmp {
                    THREAD_COUNT.deref().fetch_add(1, Ordering::SeqCst);
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

pub enum CompleteResult {
    Success = 0,
    WouldBlockLonger,
    NotFound,
}

fn wait_to_stop_executing(id: u64, iters: u8) -> CompleteResult {
    while iters != 0 {
        iters -= 1;

        loop { match JOBS_EXECUTING.deref().lock() {
            Ok(mut guard) => {
                guard.deref_mut().make_contiguous();
                for i in guard.deref().as_slices().0 {
                    if i.0 == self.id {
                        break;
                    }
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        } return CompleteResult::Success; }

        waste_cpu_cycles(1000);
    }

    CompleteResult::WouldBlockLonger
}

fn wait_to_start_executing_engine(id: u64) -> CompleteResult {
    let mut iters: u8 = COMPLETE_BLOCK_FOR;

    while iters != 0 {
        iters -= 1;

        loop { match ENGINE_JOBS_QUEUED.deref().lock() {
            Ok(mut guard) => {
                guard.deref_mut().make_contiguous();
                for i in guard.deref().as_slices().0 {
                    if i.0 == self.id {
                        break;
                    }
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        } return wait_to_stop_executing(self.id, iters + 1); }

        waste_cpu_cycles(1000);
    }

    CompleteResult::WouldBlockLonger
}

fn wait_to_start_executing(id: u64) -> CompleteResult {
    let mut iters: u8 = COMPLETE_BLOCK_FOR;

    while iters != 0 {
        iters -= 1;

        loop { match JOBS_QUEUED.deref().lock() {
            Ok(mut guard) => {
                guard.deref_mut().make_contiguous();
                for i in guard.deref().as_slices().0 {
                    if i.0 == self.id {
                        break;
                    }
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        } return wait_to_stop_executing(self.id, iters + 1); }

        waste_cpu_cycles(1000);
    }

    CompleteResult::WouldBlockLonger
}

impl JobHandle {
    pub fn complete(&self) -> CompleteResult {
        match ENGINE_JOBS_QUEUED.deref().lock() {
            Ok(mut guard) => {
                guard.deref_mut().make_contiguous();
                for i in guard.deref().as_slices().0 {
                    if i.0 == self.id {
                        return wait_to_start_executing_ENGINE(self.id);
                    }
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        }

        match JOBS_QUEUED.deref().lock() {
            Ok(mut guard) => {
                guard.deref_mut().make_contiguous();
                for i in guard.deref().as_slices().0 {
                    if i.0 == self.id {
                        return wait_to_start_executing(self.id);
                    }
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        }

        match JOBS_EXECUTING.deref().lock() {
            Ok(mut guard) => {
                guard.deref_mut().make_contiguous();
                for i in guard.deref().as_slices().0 {
                    if i.0 == self.id {
                        return wait_to_stop_executing(self.id, COMPLETE_BLOCK_FOR);
                    }
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        }

        CompleteResult::NotFound
    }

    pub fn complete_blocking(&self) -> CompleteResult {
        let mut found = false;
        let mut executing = false;
        if self.id & (1 << 63) != 0 {
            match ENGINE_JOBS_QUEUED.deref().lock() {
                Ok(mut guard) => {
                    guard.deref_mut().make_contiguous();
                    for i in guard.deref().as_slices().0 {
                        if i.0 == self.id { found = true }
                    }
                },
                Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
            }
        } else {
            match JOBS_QUEUED.deref().lock() {
                Ok(mut guard) => {
                    guard.deref_mut().make_contiguous();
                    for i in guard.deref().as_slices().0 {
                        if i.0 == self.id { found = true }
                    }
                },
                Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
            }
        }

        match JOBS_EXECUTING.deref().lock() {
            Ok(mut guard) => {
                guard.deref_mut().make_contiguous();
                for i in guard.deref().as_slices().0 {
                    if i.0 == self.id { found = true; executing = true; }
                }
            },
            Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
        }

        if found == false { return CompleteResult::NotFound; }

        loop {
            if executing {
                match JOBS_EXECUTING.deref().lock() {
                    Ok(mut guard) => {
                        guard.deref_mut().make_contiguous();
                        for i in guard.deref().as_slices().0 {
                            if i.0 == self.id { drop(guard); waste_cpu_cycles(100); continue; }

                            return CompleteResult::Success;
                        }
                    },
                    Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
                }
            } else {
                if self.id & (1 << 63) != 0 {
                    match ENGINE_JOBS_QUEUED.deref().lock() {
                        Ok(mut guard) => {
                            guard.deref_mut().make_contiguous();
                            for i in guard.deref().as_slices().0 {
                                if i.0 == self.id { drop(guard); waste_cpu_cycles(100); continue; }

                                executing = true;
                                continue;
                            }
                        },
                        Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
                    }
                } else {
                    match JOBS_QUEUED.deref().lock() {
                        Ok(mut guard) => {
                            guard.deref_mut().make_contiguous();
                            for i in guard.deref().as_slices().0 {
                                if i.0 == self.id { drop(guard); waste_cpu_cycles(100); continue; }

                                executing = true;
                                continue;
                            }
                        },
                        Err(err) => { panic!("A catastrophic jobsystem error has occured. {}", err) },
                    }
                }
            }
        }
    }
}
