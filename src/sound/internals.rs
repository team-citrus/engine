/*
*   name: src/sound/internals.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Internal variables for sound processing
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::sync::Mutex;
pub use soloud::*;

pub(super) static AUDIO_ENGINE: Mutex<Soloud>;

pub(in crate::internal::threads) fn init_soloud() -> () {
    match AUDIO_ENGINE.lock() {
        Ok(guard) => {
            *guard = Soloud::new(
                SoloudFlag::LeftHanded3D,
                Backend::Miniaudio, 
                48000 /* couldn't find actual docs, just assume Hz */, 
                1024, 
                2
            ).unwrap();
        }, // TODO: refine this.
        Err(err) => {
            panic!("The guard mutex of the audio engine has been corrupted. {}", err)
        },
    }
}
