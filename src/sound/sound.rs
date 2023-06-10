/*
*   name: src/sound/sound.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Sound structures
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use super::internals::*;
use std::{string::String, ffi::{c_void, c_char}, ops::DerefMut};
use crate::internal::vendor::__citrus_engine_vendor_file_to_slice;

pub struct Sound {
    file: String,
    handle: Handle,
}

impl Sound {
    pub fn new(filename: String) -> Sound {
        Sound { file: filename, handle: unsafe { Handle::from_raw(0) } }
    }

    pub fn play(&mut self) {
        let mut wav = audio::Wav::default();
        wav.load_mem(__citrus_engine_vendor_file_to_slice(self.file.as_bytes().as_ptr() as *const c_char, 0)).unwrap();

        match audio_engine.lock() {
            Ok(mut guard) => { self.handle = guard.deref_mut().play(&wav) },
            Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) }
        }
    }

    pub fn play_new(filename: String) -> Sound {
        let mut sound = Sound { file: filename, handle: unsafe { Handle::from_raw(0) } };
        let mut wav = audio::Wav::default();
        wav.load_mem(__citrus_engine_vendor_file_to_slice(filename.as_bytes().as_ptr() as *const c_char, 0)).unwrap();

        match audio_engine.lock() {
            Ok(mut guard) => { sound.handle = guard.deref_mut().play(&wav) },
            Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) }
        }

        sound
    }

    // TODO: stuff
}
