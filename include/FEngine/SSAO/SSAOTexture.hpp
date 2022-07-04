#ifndef SSAO_TEXTURE_H
#define SSAO_TEXTURE_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>


class SSAOTexture {
public:

     void init(unsigned int width, unsigned int height, std::vector<glm::vec3>& noise);
     void destroy();

     GLuint getID();

private:

     GLuint m_textureID = 0;


};

#endif
