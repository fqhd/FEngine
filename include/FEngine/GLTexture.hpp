#pragma once

#include <string>
#include <GLAD/glad.h>
#include <FEngine/Image.hpp>
#include <FEngine/Color.hpp>

namespace FEngine
{
    class GLTexture
    {
    public:
        void init(const char *path, Color color, bool redonly = false);
        void bind(GLenum loc) const;
        void unbind(GLenum loc);
        void destroy();

        GLuint id = 0;
    };
}