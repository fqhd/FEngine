#include <FEngine/Texture.hpp>
#include <FEngine/Image.hpp>

namespace FEngine
{
    void Texture::init(const std::string &aPath, const std::string &aoPath, Color color)
    {
        albedo.init(aPath.c_str(), color);
        ambient.init(aoPath.c_str(), Color(255, 255, 255), true);
    }

    void Texture::bind() const
    {
        albedo.bind(GL_TEXTURE0);
        ambient.bind(GL_TEXTURE1);
    }

    void Texture::unbind()
    {
        albedo.unbind(GL_TEXTURE0);
        ambient.unbind(GL_TEXTURE1);
    }

    void Texture::destroy()
    {
        albedo.destroy();
        ambient.destroy();
    }
}