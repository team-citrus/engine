/*
*   name: src/internal/gameplay.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: gameplay loop.
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{arch::asm, sync::{atomic::Ordering, Mutex}};
use crate::ecs::object::Object;

use super::sync;

#[no_mangle]
// Unfortunately, Rust doesn't let you disable optimization inside a single function, so we have to use external assembly.
extern "C" pub(crate) fn waste_cpu_cycles(cycles: i32);

struct Scene {
    objects: Vec<Object>,
    id: usize
}

static scenes: Vec<Mutex<Scene>>;

pub fn gameplay_main() -> () {
    let cur_scene: *mut Scene; // TODO: default scene.

    loop {
        // TODO: Keyboard stuff
        // TODO: load scene.

        let scene_ref:&mut Scene = unsafe { &mut *cur_scene };

        while is_render_executing.load(Ordering::SeqCst) {
            asm!("pause",);
        }
        is_gameplay_executing.store(true, Ordering::SeqCst);

        object_counter.store(0, Ordering::SeqCst);

        for obj in scene_ref.objects.as_mut_slice() {
            for c in obj.components.as_mut_slice() {
                c.deref().update();
            }
        }

        is_gameplay_executing.store(false, Ordering::SeqCst);
        waste_cpu_cycles(50);
    }
}