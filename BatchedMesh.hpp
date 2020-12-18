#ifndef BATCHED_MESH_H
#define BATCHED_MESH_H

#include "Model.hpp"

#include <GL/glew.h>


class BatchedMesh {
public:

     BatchedMesh(Model* m, GLuint o, GLuint c){
          model = m;
          offset = o;
          count = c;
     }

     Model* model;
     GLuint offset = 0;
     GLuint count = 0;


};

#endif
