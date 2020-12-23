#include "StaticTerrain.hpp"
#include "Image.hpp"


void StaticTerrain::loadFromFile(Texture* texture, const std::string& filepath, unsigned int precisionFactor, float size, float heightScale, float textureScale){

     m_texture = texture;

     Image image;
     image.loadFromFile(filepath.c_str());

     float precision = 1/(float)precisionFactor;

     //Getting width and height of terrain (number of quads on both axis)
     float width = image.getWidth() * precision;
     float height = image.getHeight() * precision;

     Pixel pixel = image.getPixel(0, 0);

     Vertex* vertices = new Vertex[width * height * 4];

     unsigned int index = 0;
     for(unsigned int z = 0; z < height; z++){
          for(unsigned int x = 0; x < width; x++){

               float h1 = image.getPixel((x/(float)width + 1/(float)width) * image.getWidth(), z/(float)height * image.getHeight()).r / 255.0f;
               vertices[index].position.x = ((x / width) + (1.0f / width)) * size;
               vertices[index].position.y = h1 * heightScale;
               vertices[index].position.z = (z / height) * size;
               vertices[index].normal.x = 0;
               vertices[index].normal.y = 1;
               vertices[index].normal.z = 0;
               vertices[index].uv.x = ((x / width) + (1.0f / width)) * textureScale;
               vertices[index].uv.y = (z / height) * textureScale;
               index++;

               float h2 = image.getPixel(x/(float)width * image.getWidth(), z/(float)height * image.getHeight()).r / 255.0f;
               vertices[index].position.x = (x / width) * size;
               vertices[index].position.y = h2 * heightScale;
               vertices[index].position.z = (z / height) * size;
               vertices[index].normal.x = 0;
               vertices[index].normal.y = 1;
               vertices[index].normal.z = 0;
               vertices[index].uv.x = (x / width) * textureScale;
               vertices[index].uv.y = (z / height) * textureScale;
               index++;

               float h3 = image.getPixel(x/(float)width * image.getWidth(), (z/(float)height + 1/(float)height) * image.getHeight()).r / 255.0f;
               vertices[index].position.x = (x / width) * size;
               vertices[index].position.y = h3 * heightScale;
               vertices[index].position.z = ((z / height) + (1.0f / height)) * size;
               vertices[index].normal.x = 0;
               vertices[index].normal.y = 1;
               vertices[index].normal.z = 0;
               vertices[index].uv.x = (x / width) * textureScale;
               vertices[index].uv.y = ((z / height) + (1.0f / height)) * textureScale;
               index++;

               float h4 = image.getPixel((x/(float)width + 1/(float)width) * image.getWidth(), (z/(float)height + 1/(float)height) * image.getHeight()).r / 255.0f;
               vertices[index].position.x = ((x / width) + (1.0f / width)) * size;
               vertices[index].position.y = h4 * heightScale;
               vertices[index].position.z = ((z / height) + (1.0f / height)) * size;
               vertices[index].normal.x = 0;
               vertices[index].normal.y = 1;
               vertices[index].normal.z = 0;
               vertices[index].uv.x = ((x / width) + (1.0f / width)) * textureScale;
               vertices[index].uv.y = ((z / height) + (1.0f / height)) * textureScale;
               index++;


          }
     }

     image.free();

     //Creating indices
     index = 0;
     unsigned int* indices = new unsigned int[width * height * 6];
     for(unsigned int i = 0; i < width * height; i++){
          indices[index++] = i * 4 + 0;
          indices[index++] = i * 4 + 1;
          indices[index++] = i * 4 + 2;
          indices[index++] = i * 4 + 0;
          indices[index++] = i * 4 + 2;
          indices[index++] = i * 4 + 3;
     }


     m_terrain.init();
     m_terrain.uploadData(vertices, width * height * 4, indices, width * height * 6);
     m_shader.init();

     //Cleanup
     delete[] vertices;
     delete[] indices;

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
     m_terrain.render();


     m_shader.unbind();
}

void StaticTerrain::destroy(){
     m_shader.destroy();
     m_terrain.destroy();
}
