#include <FEngine/GLTexture.hpp>
#include <FEngine/Image.hpp>

namespace FEngine
{
    void GLTexture::init(const char *path, Color color, bool redonly)
    {

        // Generating texture
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading in data
        Image image;
        if (image.loadFromFile(path) == 1)
        {
            if (redonly)
            {
                // Parse data into single channel red only value before sending to GPU
                unsigned char *data = (unsigned char *)malloc(sizeof(char) * image.getWidth() * image.getHeight());
                int numPixels = image.getWidth() * image.getHeight();
                int index = 0;
                for (int i = 0; i < numPixels; i += image.getNumChannels())
                {
                    index++;
                    data[index] = image.getData()[i];
                }
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, image.getWidth(), image.getHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, data);
                free(data);
            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
            }
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, &color);
        }

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
}