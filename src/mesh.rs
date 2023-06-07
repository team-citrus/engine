/*
*   name: src/mesh.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Meshes and Vertexes
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use super;
use std::ops::Index;

#[repr(C)]
#[derive(Copy, Clone, PartialEq)]
pub struct VertexWeight {
    idx: i32,
    weight: f32,
}

#[derive(Copy, Clone, PartialEq)]
pub struct Vertex {
    pos: Vector3<f32>,
    uv: Vector2<f32>,
    normal: Vector2<f32>, // I KNEW IT! NORMALS!
    bone_weights: Vec<VertexWeight>, // Perfect!
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

// TODO: turn into forward of a reference counted type similar to the old MeshBufferHandle
pub struct Mesh {
    verts: Vec<Vertex>,
    index_buf: Vec<i32>,

    // TODO: THEM BONES!
}

#[repr(C)]
pub struct CMesh {
    verts: *const CVertex,
    index_buf: *const i32,
    index_buf_len: usize,
}

impl Index<usize> for Mesh {
    type Output = Vertex;

    pub fn index(&self, idx: usize) -> &Self::Output {
        self.verts.index(self.index_buf[idx])
    }
}

impl IndexMut<usize> for Mesh {
    type Output = Vertex;

    pub fn index_mut(&self, idx: usize) -> &mut Self::Output {
        self.verts.index_mut(self.index_buf[idx])
    }
}

impl Mesh {
    pub(crate) unsafe fn create_c_repr(&self) -> CMesh {
        // TODO: this.
    }
}