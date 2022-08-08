#include <FEngine/Texture.hpp>
#include <FEngine/Image.hpp>

void Texture::init(const std::string &aPath, Color color)
{
    albedo.init(aPath.c_str(), color);
}

void Texture::bind() const
{
    albedo.bind(GL_TEXTURE0);
}

void Texture::unbind()
{
    albedo.unbind(GL_TEXTURE0);
}

void Texture::destroy()
{
    albedo.destroy();
}