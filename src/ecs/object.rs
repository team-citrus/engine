/*
*   name: src/internal/object.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Define objects
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{vec::Vec, boxed::Box, ops::{Deref, DerefMut}};
use super::component::{self, Component};

pub struct Object {
    components: Vec<Box<dyn Component>>,
    pub(crate) marked_for_death: bool,
}

impl Object {
    pub fn kill(&mut self) -> () {
        self.marked_for_death = true;
    }

    pub fn get_component<T: ? Component>(&self) -> Option<&T> {
        let id = T.component_type_id();
        for i in self.components {
            if id == i.component_type_id() {
                return Some(i.deref());
            }
        }

        None
    }

    pub fn get_mut_component<T: ? Component>(&mut self) -> Option<&mut T> {
        let id = T.component_type_id();
        for i in self.components {
            if id == i.component_type_id() {
                return Some(i.deref_mut());
            }
        }

        None
    }

    fn add_component<T: ? Component>(&mut self) -> &mut T {
        self.components.push(Box::new(T::awake()));
        self.components.last().unwrap()
    }
}