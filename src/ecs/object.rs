/*
*   name: src/internal/object.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Define objects
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{vec::Vec, boxed::Box, ops::{Deref, DerefMut}};
use super::{ComponentHandle, Component};

const OBJECT_HANDLE_MAGIC_NUMBER: i32 = 0x911628b5;

#[derive(PartialEq, Eq, Clone, Copy)]
pub struct Object {
    magic_number: i32,
    code: i64,
}

#[derive(Clone)]
pub(crate) struct ObjectInternals {
    parent: Object,
    components: Vec<ComponentHandle<dyn Component>>,
}

impl EcsHandle for Object {
    fn destroy(&mut self) {
        if self.is_valid() {
            // TODO: mark for death

            self.magic_number = 0;
            self.code = 0;
        }
    }

    fn is_valid(&self) -> bool {
        if self.magic_number == OBJECT_HANDLE_MAGIC_NUMBER {
            // TODO: Validar el código
        }
    }

    fn get_component<T>(&self) -> ComponentHandle<T> {
        let tmp: ComponentHandle<T> = ComponentHandle {
            magic_number: 0,
            code: 0,
            object: *self,
        };

        // TODO: actual code.

        tmp
    }

	fn get_object<T>(&self) -> Object {
        (*self)
    }

    fn add_component<T>(&mut self) -> ComponentHandle<T> {
        todo!();
    }

    fn get_components<T>(&self) -> Vec<ComponentHandle<T>> {
        todo!();
    }
}

impl Object {
    // TODO: algunas cosas mas
}
