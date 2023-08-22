/*
*   name: src/internal/object.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Define objects
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{
    any::{Any, TypeId},
    vec::Vec,
    boxed::Box,
    ops::{Deref, DerefMut},
    sync::Mutex,
};
use super::{ComponentHandle, Component, COMPONENTS, EcsHandle};
use crate::{SlotMap, internal, internal::gameplay::COMPONENTS_FOR_DEATH, internal::gameplay::OBJECTS_FOR_DEATH};
use lazy_static::lazy_static;

const OBJECT_HANDLE_MAGIC_NUMBER: i32 = 0x911628b5;
lazy_static! {
    pub(crate) static ref OBJECTS: Mutex<SlotMap<i32, ObjectInternals>> = {
        Mutex::new(SlotMap::with_capacity_and_key(64))
    };
}

#[derive(PartialEq, Eq, Clone, Copy)]
pub struct Object {
    magic_number: i32,
    code: i32,
}

#[derive(Clone)]
pub(crate) struct ObjectInternals {
    parent: Object,
    components: Vec<ComponentHandle<dyn Component>>,
    children: Vec<Object>
}

impl EcsHandle for Object {
    fn destroy(&mut self) {
        if self.is_valid() {
            match OBJECTS_FOR_DEATH.deref().lock() {
                Ok(mut guardia) => {
                    guardia.deref_mut().push(self.code);
                },
                Err(_) => { panic!("The whole damn thing is broke!") }
            }
        }
    }

    fn is_valid(&self) -> bool {
        if self.magic_number == OBJECT_HANDLE_MAGIC_NUMBER {
            match OBJECTS.deref().lock() {
                Ok(guardia) => {
                    guardia.deref().contains_key(self.code)
                },
                Err(_) => {
                    panic!("ECS broke!");
                    false
                }
            }
        } else {
            false
        }
    }

    fn get_component<T>(&self) -> ComponentHandle<T> {
        let mut handle = ComponentHandle::generate_invalid::<T>();

        if self.magic_number == OBJECT_HANDLE_MAGIC_NUMBER {
            match self.get_internals() {
                Some(internal) => {
                    let type_id = TypeId::of::<ComponentHandle<T>>();

                    for i in internal.components.iter() {
                        if type_id == i.type_id() {
                            handle = *i;
                            break;
                        }
                    }
                },
                None => {}
            }
        }

        handle
    }

	fn get_object<T>(&self) -> Object {
        (*self)
    }

    fn add_component<T>(&mut self) -> ComponentHandle<T> {
        if self.is_valid() {
            let new_component = ComponentHandle::new::<T>();
            new_component.object = *self;

            unsafe {
                self.get_mut_internals().unwrap_unchecked().components.push(new_component);
                new_component.access_mut().unwrap_unchecked().awake();
            }

            new_component
        } else {
            ComponentHandle::generate_invalid::<T>()
        }
    }

    fn get_components<T>(&self) -> Option<Vec<ComponentHandle<T>>> {
        todo!();
    }
}

impl Any for Object {
    fn type_id(&self) -> TypeId {
        TypeId::of::<Object>()
    }
}

impl Object {
    fn get_internals(&self) -> Option<&ObjectInternals> {
        if self.magic_number == OBJECT_HANDLE_MAGIC_NUMBER {
            match OBJECTS.deref().lock() {
                Ok(guardia) => {
                    guardia.deref().get(self.code)
                },
                Err(_) => {
                    panic!("ECS broke!");
                    None
                }
            }
        } else {
            None
        }
    }

    fn get_mut_internals(&self) -> Option<&mut ObjectInternals> {
        if self.magic_number == OBJECT_HANDLE_MAGIC_NUMBER {
            match OBJECTS.deref().lock() {
                Ok(mut guardia) => {
                    guardia.deref_mut().get_mut(self.code)
                },
                Err(_) => {
                    panic!("ECS broke!");
                    None
                }
            }
        } else {
            None
        }
    }

    // TODO: algunas cosas mas
}

pub(in super::internal::gameplay) fn terminate_object(code: i32) -> () {
    match *OBJECTS.lock() {
        Ok(mut guardia) => {
            match guardia.deref_mut().remove(code) {
                Some(object) => {
                    for i in object.children {
                        i.destroy();
                    }
                    for i in object.components {
                        i.destroy();
                    }

                    drop(object);
                },
                None => {}
            }
        },
        Err(_) => {
            panic!("ECS broke!");
        }
    }
}