/*
*   name: src/jobs.rs
*   origin: Citrus Engine
*   purpose: The Job system and public interface
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

use std::{alloc::{GlobalAlloc, System, Layout}, ffi::c_void};

#[no_mangle]
extern "C" fn memalloc(size: usize) -> *mut u8;
#[no_mangle]
extern "C" fn memfree(ptr: *mut u8) -> ();
#[no_mangle]
extern "C" fn zmalloc(nmemb: usize, size: usize) -> *mut u8;
#[no_mangle]
extern "C" fn realloc(ptr: *mut u8, size: usize) -> *mut u8;

struct MemallocAndFriends;

unsafe impl Sync for MemallocAndFriends {}

unsafe impl GlobalAlloc for MemallocAndFriends {
    unsafe fn alloc(&self, l: Layout) -> *mut u8 {
        memalloc(l.size())
    }

    unsafe fn dealloc(&self, ptr: *mut u8, l: Layout) -> () {
        memfree(ptr);
    }

    unsafe fn alloc_zeroed(&self, l: Layout) -> *mut u8 {
        zmalloc(1, l.size)
    }

    unsafe fn realloc(&self, ptr: *mut u8, l: Layout, size: usize) -> *mut u8 {
        memrealloc(ptr, size)
    }
}

#[global_allocator]
static memalloc_y_amigos: MemallocAndFriends;