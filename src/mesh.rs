/*
*   name: src/mesh.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Meshes and Vertexes
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use super;
use std::{rc::Rc, string::String, ffi::c_char, sync::atomic::AtomicBool};

#[no_mangle]
extern "C" fn has_a_mesh(string: *const c_char) -> i32;

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
    ref_count: i32,
    lock: AtomicBool,

    // TODO: THEM BONES!
}

impl MeshBufferHandle {
    pub fn get_new_handle(fname: &String) -> &MeshBufferHandle {
        // TODO: stuff.
    }

    pub fn get_new_handle_w_flags(fname: &String, flags: i32) -> &MeshBufferHandle {

    }
}

pub struct Mesh {
    handle: &MeshBufferHandle,
}
