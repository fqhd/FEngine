#ifndef BATCHED_MESH_H
#define BATCHED_MESH_H

#include "Model.hpp"
#include "Texture.hpp"

#include <GL/glew.h>


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

#endif