/*
*   name: src/internal/sync.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Syncronization variables
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::sync::atomic::AtomicBool;

static is_render_executing: AtomicBool = false;
static is_gameplay_executing: AtomicBool = false;