/*
*   name: src/internal/render.rs
*   origin: Citrus Engine
*   purpose: Provide the code for the render loop
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{time::Duration, thread, sync::atomic::Ordering, arch::asm};
use super::{sync, waste_cpu_cycles};

#[no_mangle]
extern "C" fn vk_draw() -> ();
#[no_mangle]
extern "C" fn graphics_init() -> ();

pub fn render() -> () {
    graphics_init();
    
}