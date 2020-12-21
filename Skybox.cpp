#include "Skybox.hpp"

void Skybox::init(const std::string& dayTexturePath, const std::string& nightTexturePath){
     m_cube.init();
     m_shader.init();
     m_dayTexture.loadFromDirectory(dayTexturePath);
     m_nightTexture.loadFromDirectory(nightTexturePath);
}

void Skybox::render(Camera& camera){
     m_shader.bind();
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(glm::mat4(glm::mat3(camera.getViewMatrix())));

     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_CUBE_MAP, m_dayTexture.getID());
     glDepthMask(GL_FALSE);
     glDepthFunc(GL_LEQUAL);

     m_cube.render();

     glDepthFunc(GL_LESS);
     glDepthMask(GL_TRUE);
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

     m_shader.unbind();
}

void Skybox::destroy(){
     m_dayTexture.destroy();
     m_nightTexture.destroy();
     m_cube.destroy();
     m_shader.destroy();

}
