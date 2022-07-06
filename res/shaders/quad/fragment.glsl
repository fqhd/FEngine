#version 330 core

in vec2 vUV;

uniform sampler2D ourTexture;

out vec4 outColor;

void main(){
    outColor = vec4(texture(ourTexture, vUV).rgb, 1.0);
}