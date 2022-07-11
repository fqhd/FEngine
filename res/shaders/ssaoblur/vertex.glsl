#version 330 core

layout (location = 0) in vec2 aPosition;

out vec2 vUV;

void main(){
    vUV = (aPosition + 1.0) / 2.0;
    gl_Position = vec4(aPosition, 0.0, 1.0);
}