// Since we recently overrid malloc, realloc, and free, we don't need to define STBI_MALLOC, etc.
#define STB_IMAGE_IMPLEMENTATION
#ifndef __x86_64__
#define STBI_NEON
#endif
#define STBI_MAX_DIMENSIONS 7680 * 4320 // Max image size is 8K UHD
#include <stb_image.h>