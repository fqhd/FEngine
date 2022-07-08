#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec2 vUV;
out vec3 vNormal;
out vec3 WorldPos;

void main(){
    vUV = aUV;
    
    WorldPos = (model * vec4(aPosition, 1.0)).xyz;
    vNormal = (model * vec4(aNormal, 0.0)).xyz;

    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
