#version 330 core

layout (location = 0) out vec3 fPosition;
layout (location = 1) out vec3 fNormal;
layout (location = 2) out vec4 fAlbedo;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vUV;

uniform sampler2D albedoTexture;
uniform sampler2D specularTexture;

void main(){
    fPosition = vPosition;
    fNormal = vNormal;
    fAlbedo.rgb = texture(albedoTexture, vUV).rgb;
    fAlbedo.a = texture(specularTexture, vUV).r;
}