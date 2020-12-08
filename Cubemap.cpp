#include "Cubemap.hpp"

void Cubemap::init(){

     m_cube.init();
     m_shader.init();

}

void Cubemap::update(){

}

void Cubemap::render(Camera3D& camera, Assets& assets){

     m_shader.bind();
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(glm::mat4(glm::mat3(camera.getViewMatrix())));

     glBindTexture(GL_TEXTURE_CUBE_MAP, assets.getSkyTexture()->getID());
     glDepthFunc(GL_LEQUAL);

     m_cube.render();

     glDepthFunc(GL_LESS);
     glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

     m_shader.unbind();

}

void Cubemap::destroy(){
     m_shader.destroy();
     m_cube.destroy();
}
