#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>


class Light{
public:

     glm::vec3 position;
     glm::vec3 color;

     float linear;
     float quadratic;
     float radius;

};

#endif
