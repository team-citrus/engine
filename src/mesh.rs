/*
*   name: src/mesh.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Meshes and Vertexes
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use super;
use std::{rc::Rc, string::String};

#[repr(C)]
#[derive(Copy, Clone, PartialEq)]
pub struct VertexWeight {
    idx: i32,
    weight: f32,
}

#[derive(Copy, Clone, PartialEq)]
pub struct Vertex {
    data: &CVertex,
}

#[repr(C)]
pub(crate) struct CVertex {
    pos: Vector3<f32>,
    uv: Vector2<f32>,
    normal: Vector2<f32>,
    bone_weights: *const VertexWeight,
    weight_count: usize,
}

impl Vertex {
    fn create_c_repr(&self) -> CVertex {
        CVertex { pos: self.pos, uv: self.uv, normal: self.normal, bone_weights: self.bone_weights.as_ptr(), weight_count: self.bone_weights.len(), }
    }
}

pub struct MeshBufferHandle {
    verts: *mut CVertex,
    vert_count: i32,
    index_buf: *mut i32,
    index_buffer_count: i32,

    // TODO: THEM BONES!
}

impl MeshBufferHandle {
    pub fn get_new_handle(fname: &String) -> Rc<MeshBufferHandle> {
        // TODO: stuff.
    }
}

pub struct Mesh {
    handle: Rc<MeshBufferHandle>,
}
