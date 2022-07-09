#version 330 core

const int NUM_CASCADES = 3;

in vec2 vUV;
in vec3 WorldPos;
in vec3 vNormal;

uniform sampler2D texAlbedo;
uniform sampler2D texNormal;
uniform sampler2D texSpecular;
uniform sampler2D gShadowMap[NUM_CASCADES];
uniform usampler2D idTexture[NUM_CASCADES];
uniform mat4 lightSpaceMatrices[NUM_CASCADES];
uniform float cascadePlaneDistances[NUM_CASCADES];
uniform mat4 view;
uniform float farPlane;
uniform vec3 lightDir;
uniform vec3 viewPos;
uniform int objectID;

const int cascadeCount = 3;

out vec4 outColor;

float ShadowCalculation(vec3 fragPosWorldSpace)
{
    // select cascade layer
    vec4 fragPosViewSpace = view * vec4(fragPosWorldSpace, 1.0);
    float depthValue = abs(fragPosViewSpace.z);

    int layer = -1;
    for (int i = 0; i < cascadeCount; ++i)
    {
        if (depthValue < cascadePlaneDistances[i])
        {
            layer = i;
            break;
        }
    }
    if (layer == -1)
    {
        layer = cascadeCount;
    }

    vec4 fragPosLightSpace = lightSpaceMatrices[layer] * vec4(fragPosWorldSpace, 1.0);
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if (currentDepth > 1.0)
    {
        return 0.0;
    }

    // PCF
    float shadow = 0.0;
    float width = 4096.0;
    float texelSize = 1.0 / width;
    int kernelSize = 1;
    for(int x = -kernelSize; x <= kernelSize; ++x)
    {
        for(int y = -kernelSize; y <= kernelSize; ++y)
        {
            float pcfDepth = texture(gShadowMap[layer], projCoords.xy + vec2(x, y) * texelSize).r;
            float r = texture(idTexture[layer], projCoords.xy + vec2(x, y) * texelSize).r;
            if(currentDepth > pcfDepth && objectID != r){
                shadow += 0.5;
            }
        }    
    }
    if((kernelSize % 2) != 0){
        kernelSize = kernelSize * 2 + 1;
    }else{
        kernelSize = kernelSize * 2;
    }
    shadow /= float(kernelSize * kernelSize);
        
    return 1.0 - shadow;
}

vec3 getShadowColor(int CascadeIndex, vec4 lPos)
{
    if(CascadeIndex == 0){
        return vec3(0.0, 0.0, 1.0);
    }else if(CascadeIndex == 1){
        return vec3(0.0, 1.0, 0.0);
    }else{
        return vec3(1.0, 0.0, 0.0);
    }
}


void main(){
    vec3 albedo = texture(texAlbedo, vUV).rgb;

    float factor = ShadowCalculation(WorldPos);

    outColor = vec4(albedo * factor, 1.0);
}