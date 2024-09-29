#include "sfmx_texture.h"

bool sfmx::Texture::LoadFromFile(const char* filename) {
    return texture_.loadFromFile(filename);
}
