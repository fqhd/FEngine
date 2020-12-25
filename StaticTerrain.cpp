#include "StaticTerrain.hpp"


void StaticTerrain::init(Texture* texture, const std::string& filepath, unsigned int precisionFactor, float size, float heightScale, float textureScale){

     //Loading heightmap
     Image image;
     image.loadFromFile(filepath.c_str());

     //Checking validation of image
     if(image.getWidth() != image.getHeight()){
          Utils::log("StaticTerrain: failed to load in image(wrong image format, needs to be square image)");
          return;
     }

     m_texture = texture;

     //Calculating precision
     float precision = 1/(float)precisionFactor;

     //Getting width and height of terrain (number of quads on both axis)
     unsigned int width = image.getWidth() * precision;

     //Creating vertices based on heights given by heightmap
     std::vector<Vertex> vertices;
     for(unsigned int z = 0; z < width; z++){
          for(unsigned int x = 0; x < width; x++){

               float vertexHeight = image.getPixel((x/(float)width) * image.getWidth(), (z/(float)width) * image.getWidth()).r / 255.0f;
               vertices.emplace_back(glm::vec3((x/(float)width) * size, vertexHeight * heightScale, (z/(float)width) * size), glm::vec3(0, 1, 0), glm::vec2(x/(float)width, z/(float)width));

          }
     }
     image.free();



     m_terrain.init();
     m_terrain.uploadData(vertices.data(), vertices.size());
     m_shader.init();

     //Creating indices buffer
     m_indexBuffer = Utils::createIndicesBuffer(image.getWidth(), image.getHeight());
}

void StaticTerrain::init(Texture* texture, const std::string& filepath, float size, float heightScale, float textureScale){

     //Init texture
     m_texture = texture;

     //Creating vertices
     Image image;
     image.loadFromFile(filepath.c_str(), 4);
     if(image.getWidth() != image.getHeight()){
          Utils::log("StaticTerrain: failed to load in image(wrong image format, needs to be square image)");
          return;
     }
     
     std::vector<Vertex> vertices;
     for(unsigned int z = 0; z < image.getWidth(); z++){
          for(unsigned int x = 0; x < image.getWidth(); x++){

               float vertexHeight = image.getPixel(x, z).r / 255.0f;

               vertices.emplace_back(glm::vec3(x, vertexHeight * heightScale, z), glm::vec3(0, 1, 0), glm::vec2(x/(float)image.getWidth(), z/(float)image.getWidth()));

          }
     }
     image.free();


     //Create terrain
     m_terrain.init();
     m_terrain.uploadData(vertices.data(), vertices.size());
     m_shader.init();

     //Create indices buffer
     m_indexBuffer = Utils::createIndicesBuffer(image.getWidth(), image.getHeight());

}

void StaticTerrain::render(Camera& camera){
     m_shader.bind();

     //Send camera uniforms to shader
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(camera.getViewMatrix());
     m_shader.loadModelMatrix(transform.getMatrix());

     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, m_texture->getID());

     //Rendering
     m_terrain.render(m_indexBuffer);


     m_shader.unbind();
}

void StaticTerrain::destroy(){
     m_indexBuffer.destroy();
     m_shader.destroy();
     m_terrain.destroy();
}
