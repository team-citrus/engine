fn main() {
    let mut gcc = cc::Build::new();
    gcc.cpp(true);
    // includes
    gcc.include("include");
    gcc.flag("-idirafter include/sys");

    // Compiler flags
    gcc .flag("-m64")
        .flag("-mavx2")
        .flag("-march=haswell")
        .flag("-mtune=cannonlake")
        .warnings(true);

    // source
    gcc.file("src/core/mem.c");
    gcc.file("src/core/stb_image.c");
    gcc.file("src/core/log.cpp");
    gcc.file("src/graphics/vkLoad.cpp");
    gcc.file("src/internal/cpu_waste.S");

    // finish C/C++/Asm code
    gcc.compile("c_components");

    println!("cargo:rerun-if-changed=src/core/mem.c");
    println!("cargo:rerun-if-changed=src/core/stb_image.c");
    println!("cargo:rerun-if-changed=src/core/log.cpp");
    println!("cargo:rerun-if-changed=src/graphics/vkLoad.cpp");
    println!("cargo:rerun-if-changed=src/internal/cpu_waste.S");
}
