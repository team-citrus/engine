/*
*   name: src/internal/component.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Define the component Trait
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use super::object::{self, Object};

pub trait Component {
    fn awake(owner: &mut Object) -> Self;
    fn start(&mut self) -> ();
    fn update(&mut self) -> ();

    fn get_object(&self) -> &Object;
    fn get_mut_object(&mut self) -> &mut Object;
    
    fn component_type_id() -> i32;
}