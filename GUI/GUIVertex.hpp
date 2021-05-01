#ifndef GUI_VERTEX_H
#define GUI_VERTEX_H

#include <glm/glm.hpp>


class GUIVertex {
public:

     glm::vec3 position;
     glm::vec2 uv;

     void setPosition(float x, float y);
     void setUV(float u, float v);
     void setDepth(float depth);

};
#endif
