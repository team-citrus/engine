/*
*   name: src/internal/render.rs
*   origin: Citrus Engine
*   purpose: Provide the code for the render loop
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{time::Duration, thread, sync::atomic::Ordering};
use super::{sync, waste_cpu_cycles};

#[no_mangle]
extern "C" vk_draw() -> ();

pub fn render() -> () {
    loop {
        while is_gameplay_executing {
            let obj_ctr = object_counter.load(Ordering::SeqCst);
            let obj_cnt = object_count.load(Ordering::SeqCst)
            if obj_ctr == 0 || obj_cnt == 0 || (obj_ctr as f32)/(obj_cnt as f32) < .75 {
                let dur = Duration::from_millis(5);
                thread::sleep(dur);
            } else {
                asm!("pause",);
            }
        }
        is_render_executing.store(true, Ordering::SeqCst);

        vk_draw();

        is_render_executing.store(false, Ordering::SeqCst);
        waste_cpu_cycles(2000);
    }
}