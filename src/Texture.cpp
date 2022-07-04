#include "Texture.hpp"
#include "Image.hpp"

void Texture::init(const std::string &aPath, const std::string &nPath, const std::string &sPath)
{
    albedo.init(aPath.c_str());
    normal.init(nPath.c_str());
    specular.init(sPath.c_str());
}

void Texture::bind()
{
    albedo.bind(GL_TEXTURE0);
    normal.bind(GL_TEXTURE1);
    specular.bind(GL_TEXTURE2);
}

void Texture::unbind()
{
    albedo.unbind(GL_TEXTURE0);
    normal.unbind(GL_TEXTURE1);
    specular.unbind(GL_TEXTURE2);
}

void Texture::destroy()
{
    albedo.destroy();
    normal.destroy();
    specular.destroy();
}