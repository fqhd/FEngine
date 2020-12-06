#include "StaticObjects.hpp"

void StaticObjects::init(){
     m_shader.init();
     m_renderer.init();

}

void StaticObjects::render(Camera3D& camera){
     m_shader.bind();
     m_shader.loadViewMatrix(camera.getViewMatrix());
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_renderer.render();
     m_shader.unbind();
}

void StaticObjects::destroy(){
     m_shader.destroy();
     m_renderer.destroy();
}
