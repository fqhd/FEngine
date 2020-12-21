#include "DynamicEntityRenderer.hpp"

void DynamicEntityRenderer::init(){
     m_shader.init();
}

void DynamicEntityRenderer::render(std::vector<Entity>& entities, Camera& camera){
     if(entities.empty()){
          return;
     }

     std::stable_sort(entities.begin(), entities.end(), compare);

     std::vector<glm::mat4> matrices; // Matrices for each mesh that will be rendered
     std::vector<BatchedMesh> meshes; // Batched mesh containing the model information as well as the offsent for the matrices vector and number of instances of that entity drawn to the screen

     matrices.push_back(entities[0].transform.getMatrix()); // We push back the first matrix because we need to loop through the rest and compare the second with this first one
     meshes.emplace_back(entities[0].model, entities[0].texture, 0, 1); // We add the model with the offset 0 and a count of 1

     //Looping through entities and creating list of batched meshes for optimized rendering
     for(unsigned int i = 1; i < entities.size(); i++){
          if(entities[i].model->getVaoID() != entities[i - 1].model->getVaoID()){
               meshes.emplace_back(entities[i].model, entities[i].texture, matrices.size(), 0);
          }
          meshes.back().count++;
          matrices.push_back(entities[i].transform.getMatrix());
     }

     //Binding the shader and loading information (preparing for rendering)
     m_shader.bind();

     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(camera.getViewMatrix());

     for(auto& i : meshes){

          //Sending matrix data of all instanced models to gpu matrices buffer
          glBindBuffer(GL_ARRAY_BUFFER, i.model->getIboID());
          glBufferData(GL_ARRAY_BUFFER, i.count * sizeof(glm::mat4), &matrices[i.offset], GL_STREAM_DRAW);
          glBindBuffer(GL_ARRAY_BUFFER, 0);

          //Rendering instanced models
          glBindVertexArray(i.model->getVaoID());

          //Binding proper texture
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, i.texture->getID());

          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i.model->getEboID());
          glDrawElementsInstanced(GL_TRIANGLES, i.model->getNumVertices(), GL_UNSIGNED_INT, 0, i.count);
          glBindBuffer(GL_ARRAY_BUFFER, 0);

          //Unbinding texture
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, i.texture->getID());

          glBindVertexArray(0);

     }

     m_shader.unbind();
}

bool DynamicEntityRenderer::compare(Entity a, Entity b){
     return (a.texture->getID() < b.texture->getID());
}

void DynamicEntityRenderer::destroy(){
     m_shader.destroy();
}
