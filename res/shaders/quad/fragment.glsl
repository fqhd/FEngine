#version 330 core

in vec2 vUV;

uniform sampler2D ourTexture;

out vec4 outColor;

float near_plane = 0.01;
float far_plane = 1.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));
}

void main(){
    float depthValue = texture(ourTexture, vUV).r;
    depthValue = LinearizeDepth(depthValue);
    outColor = vec4(depthValue, depthValue, depthValue, 1.0);
}