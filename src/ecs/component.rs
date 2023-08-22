/*
*   name: src/internal/component.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Define the component Trait
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use super::{Object, EcsHandle};
use crate::{SlotMap, internal::gameplay::COMPONENTS_FOR_DEATH};
use std::{
    any::{Any, TypeId},
    marker::{Sized, Copy},
    ops::{Deref, DerefMut},
    cmp::{PartialEq, Eq},
    clone::Clone,
    boxed::Box,
    mem::{MaybeUninit, drop},
    sync::Mutex,
};
use lazy_static::lazy_static;

const COMPONENT_HANDLE_MAGIC_NUMBER: i32 = 0x7ff54c5a;
lazy_static! {
    pub(crate) static ref COMPONENTS: Mutex<SlotMap<i32, Box<dyn Component>>> = {
        Mutex::new(SlotMap::with_capacity_and_key(64))
    };
}

#[derive(PartialEq, Eq, Clone, Copy)]
pub struct ComponentHandle<C: Component> {
    pub(super) magic_number: i32,
    pub(super) code: i32,
    pub(super) object: Object,
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

impl<C> EcsHandle for ComponentHandle<C> {
    fn destroy(&mut self) {
        if self.is_valid() {
            match COMPONENTS_FOR_DEATH.deref().lock() {
                Ok(mut guardia) => {
                    guardia.deref_mut().push(self.code);
                },
                Err(_) => { panic!("The whole thing broke!") }
            }
        }
    }

    fn is_valid(&self) -> bool {
        if self.magic_number == COMPONENT_HANDLE_MAGIC_NUMBER {
            match COMPONENTS.deref().lock() {
                Ok(guardia) => {
                    match guardia.deref().get(self.code) {
                        Option::Some(value) => {
                            match value.downcast_ref::<C>() {
                                Option::Some => true,
                                Option::None => false,
                            }
                        },
                        Option::None => false,
                    }
                },
                Err(_) => {
                    panic!("ECS broke.");
                    false
                }
            }
        } else {
            false
        }
    }

    fn get_component<T>(&self) -> ComponentHandle<T> {
        self.object.get_component()
    }

	fn get_object<T>(&self) -> Object {
        self.object
    }

    fn add_component<T>(&mut self) -> ComponentHandle<T> {
        self.object.add_component()
    }

    fn get_components<T>(&self) -> Vec<ComponentHandle<T>> {
        self.object.get_components()
    }
}

impl<C> Any for ComponentHandle<C> {
    fn type_id(&self) -> TypeId {
        TypeId::of::<ComponentHandle<C>>()
    }
}

impl<C> ComponentHandle<C> {
    pub fn access(&self) -> Option<&C> {
        if self.magic_number == COMPONENT_HANDLE_MAGIC_NUMBER {
            match COMPONENTS.deref().lock() {
                Ok(guardia ) => {
                    guardia.deref().get(self.code)
                },
                Err(_) => {
                    panic!("ECS broke.");
                    None
                }
            }
        }
    }

    pub fn access_mut(&mut self) -> Option<&mut C> {
        if self.magic_number == COMPONENT_HANDLE_MAGIC_NUMBER {
            match COMPONENTS.deref().lock() {
                Ok(mut guardia ) => {
                    guardia.deref_mut().get_mut(self.code)
                },
                Err(_) => {
                    panic!("ECS broke.");
                    None
                }
            }
        }
    }

    pub(crate) fn from_code<C>(code: i32, obj: Object) -> ComponentHandle<C> {
        ComponentHandle {
            magic_number: COMPONENT_HANDLE_MAGIC_NUMBER,
            code: code,
            object: obj
        }
    }

    pub fn generate_invalid<C>() -> ComponentHandle<C> {
        ComponentHandle {
            magic_number: 0,
            code: 0,
            object: Object { magic_number: 0, code: 0}
        }
    }

    pub(crate) fn new<C>() -> ComponentHandle<C> {
        ComponentHandle {
            magic_number: COMPONENT_HANDLE_MAGIC_NUMBER,
            code: COMPONENTS.deref().insert(
                unsafe { MaybeUninit::<C>::zeroed().assume_init() }
            ),
            object: Object { magic_number: 0, code: 0 }
        }
    }
}

pub(in super::internal::gameplay) fn terminate_component(code: i32) {
    match *COMPONENTS.lock() {
        Ok(mut guardia) => {
            match guardia.deref_mut().remove(code) {
                Some(component) => {
                    *component.on_death();
                    drop(component);
                },
                None => {}
            }
        },
        Err(_) => {
            panic!("ECS broke!");
        }
    }
}