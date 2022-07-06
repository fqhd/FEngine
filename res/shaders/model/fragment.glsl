#version 330 core

in vec2 vUV;

uniform sampler2D texAlbedo;
uniform sampler2D texNormal;
uniform sampler2D texSpecular;
uniform sampler2D cascade1;
uniform sampler2D cascade2;
uniform sampler2D cascade3;

out vec4 outColor;

void main(){
    vec3 albedo = texture(texAlbedo, vUV).rgb;
    outColor = vec4(albedo, 1.0);
}