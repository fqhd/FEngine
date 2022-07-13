#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in uint aID;

out vec2 vUV;
out vec3 vPosition;
out vec3 vNormal;
flat out uint vID;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    vec4 worldViewPosition = view * model * vec4(aPosition, 1.0);
    gl_Position = projection * worldViewPosition;
    vID = aID;

    vPosition = worldViewPosition.xyz;
    vNormal = (model * vec4(aNormal, 0.0)).xyz;
    vUV = aUV;
}