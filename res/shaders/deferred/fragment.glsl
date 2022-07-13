#version 330 core

layout (location = 0) out vec3 fPosition;
layout (location = 1) out vec3 fNormal;
layout (location = 2) out vec4 fAlbedo;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vUV;
flat in uint vID;

uniform sampler2D albedoTexture;

void main(){
    fPosition = vPosition;
    fNormal = normalize(vNormal);
    fAlbedo.rgb = texture(albedoTexture, vUV).rgb;
    fAlbedo.a = float(vID) / 255.0;
}