LOAD_AS_STRING(
const int NUM_CASCADES = 3;
const int cascadeCount = 3;

in vec2 vUV;
in vec3 vNormal;
in vec3 vWorldSpacePosition;

uniform sampler2D albedoTexture;
uniform sampler2D ambientTexture;
uniform sampler2DArray gShadowMap;
uniform mat4 lightSpaceMatrices[NUM_CASCADES];
uniform float cascadePlaneDistances[NUM_CASCADES];
uniform mat4 view;
uniform vec3 lightDir;

out vec4 outColor;

float ShadowCalculation(vec3 fragPosViewSpace)
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

    float bias = 0.000125;

    // PCF
    float shadow = 0.0;
    float width = 4096.0;
    float texelSize = 1.0 / width;
    int kernelSize = 2;
    for(int x = -kernelSize; x <= kernelSize; ++x)
    {
        for(int y = -kernelSize; y <= kernelSize; ++y)
        {
            float pcfDepth = texture(gShadowMap, vec3(projCoords.xy + vec2(x, y) * texelSize, layer)).r;
            if(currentDepth - bias > pcfDepth){
                shadow += 0.6;
            }
        }
    }
    shadow /= 25.0;
        
    return 1.0 - shadow;
}

void main(){
    vec3 color = texture(albedoTexture, vec2(vUV.x, 1.0 - vUV.y)).rgb;
    float ambient = texture(ambientTexture, vUV).r;
    vec3 worldPos = vWorldSpacePosition;
    float shadowFactor = ShadowCalculation(worldPos);
    float brightness = max(dot(lightDir, normalize(vNormal)), 0.4);
    brightness = min(brightness, shadowFactor);
    outColor = vec4(color * brightness * 1.5 * ambient, 1.0);
}
)