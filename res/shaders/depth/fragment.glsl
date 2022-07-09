#version 330 core

uniform int objectID;

out uvec4 outColor;

void main(){
    outColor = uvec4(float(objectID), 0.0, 0.0, 0.0);
}