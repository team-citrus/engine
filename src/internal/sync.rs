/*
*   name: src/internal/sync.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Syncronization variables
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::sync::{atomic::{AtomicBool, AtomicI32}, Mutex};
use lazy_static::lazy_static;

pub(super) enum Executing {
    Gameplay, Render, Physics, None,
}

lazy_static! {
    pub(super) static ref EXECUTING_MUTEX: Mutex<Executing> = Mutex::new(Executing::None);
    pub(super) static ref ECS_ITER_MUTEX: Mutex<Executing> = Mutex::new(Executing::None);
    pub(super) static ref NEW_SCENE_LOADING: AtomicBool = AtomicBool::new(true);
    pub(super) static ref SCENE_CODE: AtomicI32 = AtomicI32::new(0);
}