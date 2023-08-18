/*
*   name: src/internal/component.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Define the component Trait
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use super::{Object, EcsHandle};
use std::{any::Any, marker::{Sized, Copy}, ops::{Deref, DerefMut}, cmp::{PartialEq, Eq}, clone::Clone};

const COMPONENT_HANDLE_MAGIC_NUMBER: i32 = 0x7ff54c5a;

#[derive(PartialEq, Eq, Clone, Copy)]
pub struct ComponentHandle<C: Component> {
    magic_number: i32,
    code: i64,
    object: Object,
}

pub trait Component: Any + Sized {
    fn start(&mut self) {}
    fn awake(&mut self) {}

    fn update(&mut self) {}
    fn post_update(&mut self) {}
    fn physics_update(&mut self) {}
    fn gui_update(&mut self) {}

    fn on_collision_start(&mut self /* TODO: algunas cosas mas */) {}
    fn on_collision_stop(&mut self /* TODO: algunas cosas mas */) {}
    fn on_collision(&mut self /* TODO: algunas cosas mas */) {}

    fn on_trigger_enter(&mut self /* TODO: algunas cosas mas */) {}
    fn on_trigger_exit(&mut self /* TODO: algunas cosas mas */) {}
    fn on_trigger(&mut self /* TODO: algunas cosas mas */) {}

    fn on_enable(&mut self) {}
    fn on_disable(&mut self) {}
    fn on_death(&mut self) {}

    // TODO: algunas cosas mas
}

impl EcsHandle for ComponentHandle<C> {
    fn destroy(&mut self) {
        if self.is_valid() {
            // TODO: mark for death

            self.magic_number = 0;
            self.code = 0;
        }
    }

    fn is_valid(&self) -> bool {
        if self.magic_number == COMPONENT_HANDLE_MAGIC_NUMBER {
            // TODO: Validar el código
        }
    }

    fn get_component<T>(&self) -> ComponentHandle<T> {
        self.object.get_component()
    }

	fn get_object<T>(&self) -> Object {
        self.object
    }
}

// TODO: Terminar de implementar el acceso a los Components desde ComponentHandles, al estilo de std::sync::Mutex y std::sync::MutexGuard
