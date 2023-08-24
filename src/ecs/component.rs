/*
*   name: src/internal/component.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Define the component Trait
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use super::{Object, EcsHandle};
use crate::{SlotMap, internal::{gameplay::COMPONENTS_FOR_DEATH, util::handle_mutex}};
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
    fn start(&mut self, handle: ComponentHandle<Self>) {}
    fn awake(&mut self, handle: ComponentHandle<Self>) {}

    fn update(&mut self, handle: ComponentHandle<Self>) {}
    fn post_update(&mut self, handle: ComponentHandle<Self>) {}
    fn physics_update(&mut self, handle: ComponentHandle<Self>) {}
    fn gui_update(&mut self, handle: ComponentHandle<Self>) {}

    fn on_collision_start(&mut self, handle: ComponentHandle<Self> /* TODO: algunas cosas mas */) {}
    fn on_collision_stop(&mut self, handle: ComponentHandle<Self> /* TODO: algunas cosas mas */) {}
    fn on_collision(&mut self, handle: ComponentHandle<Self> /* TODO: algunas cosas mas */) {}

    fn on_trigger_enter(&mut self, handle: ComponentHandle<Self> /* TODO: algunas cosas mas */) {}
    fn on_trigger_exit(&mut self, handle: ComponentHandle<Self> /* TODO: algunas cosas mas */) {}
    fn on_trigger(&mut self, handle: ComponentHandle<Self> /* TODO: algunas cosas mas */) {}

    fn on_enable(&mut self, handle: ComponentHandle<Self>) {}
    fn on_disable(&mut self, handle: ComponentHandle<Self>) {}
    fn on_death(&mut self, handle: ComponentHandle<Self>) {}

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
        let mut result = false;
        if self.magic_number == COMPONENT_HANDLE_MAGIC_NUMBER {
            handle_mutex(
                COMPONENTS.deref(), 
                |map: &SlotMap<i32, Box<dyn Component>>| {
                    result = match map.get(self.code) {
                        Option::Some(value) => {
                            match value.downcast_ref::<C>() {
                                Option::Some => true,
                                Option::None => false,
                            }
                        },
                        Option::None => false,
                    };
                }
            );
        }

        result
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
                Ok(mut guardia) => {
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

pub(in crate::internal::gameplay) fn terminate_component(comp: ComponentHandle<dyn Component>) {
    handle_mutex(COMPONENTS.deref(), |components: &mut SlotMap<i32, Box<dyn Component>>| {
        match components.remove(comp.code) {
            Some(component) => {
                component.deref_mut().on_death(comp);
                drop(component);
            },
            None => ()
        }
    });
}