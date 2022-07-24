#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in mat4 aModel;

void main(){
    gl_Position = aModel * vec4(aPosition, 1.0);
}