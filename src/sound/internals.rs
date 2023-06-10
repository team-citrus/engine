/*
*   name: src/sound/internals.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Internal variables for sound processing
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::sync::Mutex;
pub use soloud::{Soloud, SoloudFlag, Backend};

pub static audio_engine: Mutex<Soloud>;

pub(crate) fn init_soloud() -> () {
    match audio_engine.lock() {
        Ok(guard) => { *guard.deref_mut() = Soloud::new(SoloudFlag::LeftHanded3D, Backend::Miniaudio,
            48000 /* couldn't find actual docs, just assume Hz */, 1024, 2).unwrap(); }, // TODO: refine this.
        Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) },
    }
}
