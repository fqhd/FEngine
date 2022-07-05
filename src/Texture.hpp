#pragma once

#include <string>
#include <GL/glew.h>
#include "GLTexture.hpp"

struct Texture {
    GLTexture albedo;
    GLTexture normal;
    GLTexture specular;
};
