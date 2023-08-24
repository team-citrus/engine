/*
*   name: src/internal/gameplay.rs
*   origin: Citrus Engine
*   purpose: Utility functions for internals
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{sync::Mutex, option::Option, ops::{Deref, DerefMut}};

pub fn handle_mutex<T, F: FnOnce()>(mutex: &Mutex<T>, func: F) {
    match mutex.lock() {
        Ok(mut guard) => func(guard.deref_mut()),
        Err(_) => todo!("Panic"),
    }

    ()
}