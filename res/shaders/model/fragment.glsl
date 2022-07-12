#version 330 core

const int NUM_CASCADES = 3;
const int cascadeCount = 3;

in vec2 vUV;

uniform sampler2D texAlbedo;
uniform sampler2D texNormal;
uniform sampler2D texSpecular;
uniform sampler2D texPosition;
uniform sampler2D gShadowMap[NUM_CASCADES];
uniform sampler2D ssaoTexture;
uniform mat4 lightSpaceMatrices[NUM_CASCADES];
uniform float cascadePlaneDistances[NUM_CASCADES];
uniform mat4 view;
uniform float farPlane;
uniform vec3 lightDir;
uniform vec3 viewPos;


out vec4 outColor;

float ShadowCalculation(vec3 fragPosViewSpace, vec3 normal)
{
    // select cascade layer
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
    vec3 fragPosWorldSpace = (inverse(view) * vec4(fragPosViewSpace, 1.0)).xyz;
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
    int kernelSize = 2;
    for(int x = -kernelSize; x <= kernelSize; ++x)
    {
        for(int y = -kernelSize; y <= kernelSize; ++y)
        {
            float pcfDepth = texture(gShadowMap[layer], projCoords.xy + vec2(x, y) * texelSize).r;
            if(currentDepth > pcfDepth){
                shadow += 0.6;
            }
        }
    }
    shadow /= 25.0;
        
    return 1.0 - shadow;
}

void main(){
    vec3 albedo = texture(texAlbedo, vUV).rgb;
    float ssao = texture(ssaoTexture, vUV).r;
    vec3 worldPos = texture(texPosition, vUV).rgb;

    vec3 normal = texture(texNormal, vUV).rgb;
    float shadowFactor = ShadowCalculation(worldPos, normal);
    float brightness = max(dot(normal, lightDir), 0.4);

    outColor = vec4(albedo * ssao * shadowFactor, 1.0);
}