use glm::vec3;

/*
*   name: src/sound/sound.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Sound structures
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
use super::internals::*;
use std::{string::String, ffi::{c_void, c_char}, ops::DerefMut};
use crate::{internal::vendor::__citrus_engine_vendor_file_to_slice, Vec3};

pub struct Mixer {
    owner: Option<&Mixer>,
    sub: Vec<Mixer>,
    sounds: Vec<Sound>,
    pan: f32,
    volume: f32,
    position: Vec3<f32>,
}

impl Mixer {
    pub fn default() -> Mixer {
        Mixer { owner: None, sub: Vec::with_capacity(1), sounds: Vec::with_capacity(8), pan: 0, volume: 100, position: vec3(0, 0, 0) }
    }

    pub fn new(pan: f32, volume: f32, position: Vec3<f32>) -> Mixer {
        Mixer { owner: None, sub: Vec::with_capacity(1), sounds: Vec::with_capacity(8), pan: pan, volume: volume, position: position }
    }

    pub fn default_child(&mut self) -> Mixer {
        let child = Mixer { owner: Some(&self as &Mixer), sub: Vec::with_capacity(1), sounds: Vec::with_capacity(8), pan: 0, volume: 100, position: vec3(0, 0, 0) };
        self.sub.push(child);
        child
    }

    pub fn new_child(pan: f32, volume: f32, position: Vec3<f32>) -> Mixer {
        let child = Mixer { owner: Some(&self as &Mixer), sub: Vec::with_capacity(1), sounds: Vec::with_capacity(8), pan: pan, volume: volume, position: position };
        self.sub.push(child);
        child
    }

    // TODO: Stuff
}

pub struct Sound {
    file: String,
    handle: Handle,
    is3d: bool,
    pan: f32,
    volume: f32,
    position: Vec3<f32>,
    parent: Option<&Mixer>,
}

impl Sound {
    pub fn default(filename: String) -> Sound {
        Sound { file: filename, handle: unsafe { Handle::from_raw(0) }, is3d: false, pan: 0.0, volume: 0.0, position: vec3(0.0, 0.0, 0.0), parent: None }
    }

    pub fn play(&mut self) {
        let mut wav = audio::Wav::default();
        wav.load_mem(__citrus_engine_vendor_file_to_slice(self.file.as_bytes().as_ptr() as *const c_char, 0)).unwrap();

        match audio_engine.lock() {
            Ok(mut guard) => { self.handle = guard.deref_mut().play(&wav) },
            Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) }
        }
    }

    pub fn play_new_default(filename: String) -> Sound {
        let mut sound = Sound { file: filename, handle: unsafe { Handle::from_raw(0) }, is3d: false, pan: 0.0, volume: 0.0, position: vec3(0.0, 0.0, 0.0), parent: None };
        let mut wav = audio::Wav::default();
        wav.load_mem(__citrus_engine_vendor_file_to_slice(filename.as_bytes().as_ptr() as *const c_char, 0)).unwrap();

        match audio_engine.lock() {
            Ok(mut guard) => { sound.handle = guard.deref_mut().play(&wav) },
            Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) }
        }

        sound
    }

    pub fn play_delayed(&mut self, time: f64) {
        let mut wav = audio::Wav::default();
        wav.load_mem(__citrus_engine_vendor_file_to_slice(self.file.as_bytes().as_ptr() as *const c_char, 0)).unwrap();

        match audio_engine.lock() {
            Ok(mut guard) => { self.handle = guard.deref_mut().play_clocked(time, &wav) },
            Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) }
        }
    }

    pub fn play_delayed_new_default(filename: String, time: f64) -> Sound {
        let mut sound = Sound { file: filename, handle: unsafe { Handle::from_raw(0) }, is3d: false, pan: 0.0, volume: 0.0, position: vec3(0.0, 0.0, 0.0), parent: None };
        let mut wav = audio::Wav::default();
        wav.load_mem(__citrus_engine_vendor_file_to_slice(filename.as_bytes().as_ptr() as *const c_char, 0)).unwrap();

        match audio_engine.lock() {
            Ok(mut guard) => { sound.handle = guard.deref_mut().play_clocked(time, &wav) },
            Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) }
        }

        sound
    }

    pub fn pause(&mut self) -> () {
        match audio_engine.lock() {
            Ok(guard) => { guard.deref().pause(self.handle) },
            Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) }
        }
    }
    // TODO: stuff
}
