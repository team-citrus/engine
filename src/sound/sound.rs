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
    sounds: Vec<Sound>,
    volume: f32,
    int_repr: audio::Bus,
}

impl Mixer {
    pub fn default() -> Mixer {
        Mixer { sounds: Vec<Sound>::with_capacity(8), volume: 1.0, int_repr: audio::Bus::default() }
    }

    pub fn set_volume(&mut self, volume: f32) -> () {
        self.volume = volume;
        self.int_repr.set_volume(volume);
    }

    pub fn get_volume(&self) -> f32 {
        self.volume
    }

    pub fn default_sound(&mut self, filename: String) -> &Sound {
       let tmp = Sound { file: filename, handle: unsafe { Handle::from_raw(0) }, is3d: false, pan: 0.0, volume: 1.0, position: vec3(0.0, 0.0, 0.0), parent: Some(&*self) };
       self.sounds.push(tmp);
       self.sounds.last().unwrap()
    }

    pub fn new_sound(&mut self, filename: String, pan: f32, volume: f32) -> &Sound {
        let tmp = Sound { file: filename, handle: unsafe { Handle::from_raw(0) }, is3d: false, pan: pan, volume: volume, position: vec3(0.0, 0.0, 0.0), parent: Some(&*self) };
        self.sounds.push(tmp);
        self.sounds.last().unwrap()
    }

    pub fn default_sound_3d(&mut self, filename: String, position: Vec3<f32>) -> &Sound {
        let tmp = Sound { file: filename, handle: unsafe {  Handle::from_raw(0) }, is3d: true, pan: 0.0, volume: 1.0, position: position, parent: Some(&*self) };
        self.sounds.push(tmp);
        self.sounds.last().unwrap()
    }

    pub fn new_sound_3d(&mut self, filename: String, position: Vec3<f32>, volume: f32) -> &Sound {
        let tmp = Sound { file: filename, handle: unsafe { Handle::from_raw(0) }, is3d: true, pan: 0.0, volume: volume, position: position, parent: Some(&*self) };
        self.sounds.push(tmp);
        self.sounds.last().unwrap()
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
        Sound { file: filename, handle: unsafe { Handle::from_raw(0) }, is3d: false, pan: 0.0, volume: 1.0, position: vec3(0.0, 0.0, 0.0), parent: None }
    }

    pub fn new(filename: String, pan: f32, volume: f32) -> Sound {
        Sound { file: filename, handle: unsafe { Handle::from_raw(0) }, is3d: false, pan: pan, volume: volume, position: vec3(0.0, 0.0, 0.0), parent: None }
    }

    pub fn default_3d(filename: String, position: Vec3<f32>) -> Sound {
        Sound { file: filename, handle: unsafe {  Handle::from_raw(0) }, is3d: true, pan: 0.0, volume: 1.0, position: position, parent: None }
    }

    pub fn new_3d(filename: String, position: Vec3<f32>, volume: f32) -> Sound {
        Sound { file: filename, handle: unsafe { Handle::from_raw(0) }, is3d: true, pan: 0.0, volume: volume, position: position, parent: None }
    }

    pub fn play(&mut self, start_paused: bool) {
        let mut wav = audio::Wav::default();
        wav.load_mem(__citrus_engine_vendor_file_to_slice(self.file.as_bytes().as_ptr() as *const c_char, 0)).unwrap();

        match audio_engine.lock() {
            Ok(mut guard) => {
                if self.is3d {
                    self.handle = match self.parent {
                        Some(handle) => {
                            let tmp = handle.int_repr.play_3d_ex(&wav, self.position.x, self.position.y, self.position.z, 0.0, 0.0, 0.0, self.volume, start_paused);
                            self.parent = Some(handle);
                            tmp
                        },
                        None => {
                            self.parent = None;
                            guard.deref_mut().play_3d_ex(&wav, self.position.x, self.position.y, self.position.z, 0.0, 0.0, 0.0, self.volume, start_paused, unsafe { Handle::from_raw(0) })
                        }
                    };
                } else {
                    self.handle = match self.parent {
                        Some(handle) => {
                            let tmp = handle.play_ex(&wav, self.volume, self.pan, start_paused);
                            self.parent = Some(handle);
                            tmp
                        },
                        None => {
                            self.parent = None;
                            guard.deref_mut().play_ex(&wav, self.volume, self.pan, start_paused, unsafe { Handle::from_raw(0) })
                        }
                    };
                }
            },
            Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) }
        }
    }

    pub fn pause(&mut self) -> () {
        match audio_engine.lock() {
            Ok(guard) => { guard.deref().pause(self.handle) },
            Err(err) => { panic!("The guard mutex of the audio engine has been corrupted. {}", err) }
        }
    }
    // TODO: stuff
}
