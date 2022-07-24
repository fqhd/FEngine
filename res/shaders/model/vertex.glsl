#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in mat4 aModel;
layout (location = 6) in vec3 aColor;

out vec3 vColor;
out vec3 vNormal;
out vec3 vWorldSpacePosition;

uniform mat4 projection;
uniform mat4 view;

void main(){
    vColor = aColor;
    vNormal = (aModel * vec4(aNormal, 0.0)).xyz;
    vec4 wPos = view * aModel * vec4(aPosition, 1.0);
    vWorldSpacePosition = wPos.xyz;
    gl_Position = projection * wPos;
}
