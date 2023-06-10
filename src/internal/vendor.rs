/*
*   name: src/internal/vendor.rs
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: Vendor interface Rust version
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{ffi::{c_void, c_char}};

const CITRUS_ENGINE_VENDOR_READ: i32 = 4;
const CITRUS_ENGINE_VENDOR_WRITE: i32 = 2;
const CITRUS_ENGINE_VENDOR_EXECUTE: i32 = 1;

pub struct File;

#[no_mangle]
pub extern "C" fn __citrus_engine_vendor_map_file_to_mem(name: *const c_char, offset: usize, len: usize, perms: i32) -> *mut c_void;

#[no_mangle]
pub extern "C" fn __citrus_engine_vendor_file_to_slice(name: *const c_char, offset: usize) -> &mut [u8];

#[no_mangle]
pub extern "C" fn __citrus_engine_vendor_unmap_file_from_mem(ptr: *mut c_void, len: usize) -> ();

// TODO: rest.
