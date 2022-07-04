#pragma once

#include "Model.hpp"
#include "Texture.hpp"

#include <GL/glad.h>


class BatchedMesh {
public:

     BatchedMesh(Model* m, Texture* t, GLuint o, GLuint c){
          model = m;
          texture = t;
          offset = o;
          count = c;
     }

     Model* model;
     Texture* texture;
     GLuint offset = 0;
     GLuint count = 0;



};