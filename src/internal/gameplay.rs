/*
*   name: src/internal/gameplay.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: gameplay loop.
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{arch::asm, sync::{atomic::Ordering, Mutex}};
use crate::ecs::*;
use super::sync;
use lazy_static::lazy_static;

#[no_mangle]
// Unfortunately, Rust doesn't let you disable optimization inside a single function, so we have to use external assembly.
pub(crate) extern "C" fn waste_cpu_cycles(cycles: i32);

lazy_static! {
    pub(crate) static ref OBJECTS_FOR_DEATH: Mutex<Vec<i32>> = {
        Mutex::new(Vec::with_capacity(32))
    };
    pub(crate) static ref COMPONENTS_FOR_DEATH: Mutex<Vec<i32>> = {
        Mutex::new(Vec::with_capacity(32))
    };
    pub(crate) static ref COMPONENTS_ON_START: Mutex<Vec<i32>> = {
        Mutex::new(Vec::with_capacity(32))
    };
}

pub fn gameplay_main() -> () {
    // TODO: scene loading, etc.

    loop {


        // TODO: scene unloading, ECS unloading, etc.
    }
}