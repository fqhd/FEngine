#include "TextureManager.hpp"

void TextureManager::init()
{
    // Create default textures
}

Texture TextureManager::loadTexture(const std::string &aPath, const std::string &nPath, const std::string &sPath)
{
    Texture texture;
    texture.albedo.init(aPath.c_str(), defaultAlbedo);
    texture.normal.init(nPath.c_str(), defaultNormal);
    texture.specular.init(sPath.c_str(), defaultSpecular);
    return texture;
}

void TextureManager::bindTexture(const Texture &texture) const
{
    texture.albedo.bind(GL_TEXTURE0);
    texture.normal.bind(GL_TEXTURE1);
    texture.specular.bind(GL_TEXTURE2);
}

void TextureManager::unbindTexture(const Texture &texture) const
{
    texture.albedo.unbind(GL_TEXTURE0);
    texture.normal.unbind(GL_TEXTURE1);
    texture.specular.unbind(GL_TEXTURE2);
}

void TextureManager::destroyTexture(Texture& texture){
    texture.albedo.destroy();
    texture.normal.destroy();
    texture.specular.destroy();

    // Destroy default textures
}