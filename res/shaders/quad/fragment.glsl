#version 330 core

in vec2 vUV;

uniform sampler2D ourTexture;

out vec4 outColor;

void main(){
    float depthValue = texture(ourTexture, vUV).r;
    outColor = vec4(depthValue, depthValue, depthValue, 1.0);
}