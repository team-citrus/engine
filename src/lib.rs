/*
*   name: src/lib.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: lib.rs
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

pub mod internal;
pub mod ecs;
pub mod jobs;
pub use glm::*;
pub use glm::builtin::*;
pub use slotmap::*;
pub mod mesh;
pub mod sound;
