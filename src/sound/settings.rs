use std::ops::DerefMut;

/*
*   name: src/sound/settings.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Internal variables for sound processing
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
use super::internals::{Soloud, AUDIO_ENGINE};

pub fn get_samplerate() -> u32 {
    match AUDIO_ENGINE.lock() {
        Ok(guard) => { guard.deref().backend_samplerate() },
        Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err); },
    }
}

pub fn get_channel_count() -> u32 {
    match AUDIO_ENGINE.lock() {
        Ok(guard) => { guard.deref().backend_channels() },
        Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err); },
    }
}

pub fn get_buffer_size() -> u32 {
    match AUDIO_ENGINE.lock() {
        Ok(guard) => { guard.deref().backend_buffer_size() },
        Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err); },
    }
}

// TODO: the setters? somehow?
