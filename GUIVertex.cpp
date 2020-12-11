#include "GUIVertex.hpp"

void GUIVertex::setPosition(float x, float y) {
     position.x = x;
     position.y = y;
}

void GUIVertex::setUV(float u, float v) {
     uv.x = u;
     uv.y = v;
}

void GUIVertex::setDepth(float depth){
     position.z = depth;
}
