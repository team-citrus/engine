/*
*   name: src/internal/mod.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: mod.rs for the internal module
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

pub mod gameplay;
pub mod render;
pub mod threads;
pub(crate) mod vendor;
mod alloc;
mod sync;
pub(crate) mod util;