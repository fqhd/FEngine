#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 vUV;
out vec3 vNormal;
out vec3 vWorldSpacePosition;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main(){
    vUV = aUV;
    vNormal = aNormal;
    vec4 wPos = view * model * vec4(aPosition);
    vWorldSpacePosition = wPos.xyz;
    gl_Position = projection * wPos;
}
