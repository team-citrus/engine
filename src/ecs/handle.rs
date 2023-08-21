/*
*   name: src/internal/handle.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Define ECS handles
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
use std::{clone::Clone, cmp::Eq, marker::Sized};
use super::{ComponentHandle, Object};

pub trait EcsHandle: Clone + Eq + Sized {
    fn destroy(&mut self);
    fn is_valid(&self) -> bool;

	fn get_component<T>(&self) -> ComponentHandle<T>;
	fn get_object<T>(&self) -> Object;

    // TODO: algo
}
