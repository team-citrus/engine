/*
*   name: src/internal/gameplay.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: gameplay loop.
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{arch::asm, sync::{atomic::Ordering, Mutex}, ops::{Deref, DerefMut}};
use crate::ecs::*;
use super::{sync::{self, NEW_SCENE_LOADING}, util};
use lazy_static::lazy_static;

#[no_mangle]
// Unfortunately, Rust doesn't let you disable optimization inside a single function, so we have to use external assembly.
pub(crate) extern "C" fn waste_cpu_cycles(cycles: i32);

lazy_static! {
    pub(crate) static ref OBJECTS_FOR_DEATH: Mutex<Vec<Object>> = {
        Mutex::new(Vec::with_capacity(32))
    };
    pub(crate) static ref COMPONENTS_FOR_DEATH: Mutex<Vec<i32>> = {
        Mutex::new(Vec::with_capacity(32))
    };
    pub(crate) static ref COMPONENTS_ON_START: Mutex<Vec<ComponentHandle<dyn Component>>> = {
        Mutex::new(Vec::with_capacity(32))
    };
}

fn loop_inner() -> () {
    // First thing's first, handle everything marked for death.
    
    util::handle_mutex(OBJECTS_FOR_DEATH.deref(), |vector: &Vec<Object>| {
        for i in *vector {
            terminate_object(i, vector);
        }
        vector.clear();
    });

    util::handle_mutex(COMPONENTS_FOR_DEATH.deref(), |vector: &Vec<ComponentHandle<dyn Component>>| {
        for i in *vector {
            terminate_component(i);
        }
        vector.clear();
    });

    // Next handle everything to be started

    util::handle_mutex(COMPONENTS_ON_START.deref(), |vector: &Vec<ComponentHandle<dyn Component>>| {
        for i in *vector {
            match i.access_mut() {
                Some(component) => component.start(i),
                None => (),
            }
        }
        vector.clear();
    });

    // Finally, handle updating.
    util::handle_mutex(OBJECTS.deref(), |vector: &Vec<Object>| {
        for i in vector {
            i.update();
        }
    });
}

pub fn gameplay_main() -> () {
    // TODO: scene loading, etc.

    loop {
        while *NEW_SCENE_LOADING.load(Ordering::SeqCst) == false {
            loop_inner();
        }

        // TODO: scene unloading, ECS unloading, etc.
    }
}