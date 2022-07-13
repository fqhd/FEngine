#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 3) in uint aID;

uniform mat4 model;

flat out uint vID;

void main(){
    vID = aID;
    gl_Position = model * vec4(aPosition, 1.0);
}