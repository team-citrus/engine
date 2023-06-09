/*
*   name: src/internal/threads.rs
*   origin: Citrus Engine
*   purpose: Provide the code that forks into the new threads
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{thread, sync::atomic::Ordering};
use super::*;

pub fn enter_threads() -> () {
    is_render_executing.store(false, Ordering::Relaxed);
    is_gameplay_executing.store(true, Ordering::Relaxed);

    // There is a behind the scenes audio thread that we have no control over, not even soloud does.
    // We simply have to trust soloud to do what is best for us.
    sound::internals::init_soloud();
    
    thread::spawn(|| render::render());
    gameplay();
}