#include "GLTexture.hpp"
#include "Image.hpp"

void GLTexture::init(const char *path)
{
    // Loading in data
    Image image;
    image.loadFromFile(path);

    // Generating texture
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    image.free();
}

void GLTexture::bind(GLenum loc) const
{
    glActiveTexture(loc);
    glBindTexture(GL_TEXTURE_2D, id);
}

void GLTexture::unbind(GLenum loc)
{
    glActiveTexture(loc);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture::destroy()
{
    glDeleteTextures(1, &id);
}