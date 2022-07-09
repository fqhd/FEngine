#version 330 core

uniform int objectID;

out vec4 outColor;

void main(){
    outColor = vec4(float(objectID), 0.0, 0.0, 0.0);
}