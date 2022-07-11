#version 330 core

in vec2 vUV;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D texNoise;
uniform vec3 samples[32];
uniform mat4 projection;
uniform mat4 view;
uniform int screenWidth;
uniform int screenHeight;
uniform int kernelSize;
out float FragColor;

const float radius = 0.5;
const float bias = 0.025;

void main(){
    vec2 noiseScale = vec2(screenWidth, screenHeight) / 4.0;
    vec3 fragPos   = texture(gPosition, vUV).rgb;
    vec4 normal    = (view * vec4(texture(gNormal, vUV).rgb, 0.0));
    vec3 randomVec = texture(texNoise, vUV * noiseScale).xyz;
    vec3 tangent   = normalize(randomVec - normal.xyz * dot(randomVec, normal.xyz));
    vec3 bitangent = cross(normal.xyz, tangent);
    mat3 TBN       = mat3(tangent, bitangent, normal.xyz);
    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; ++i)
    {
        // get sample position
        vec3 samplePos = TBN * samples[i]; // from tangent to view-space
        samplePos = fragPos + samplePos * radius;
        vec4 offset = vec4(samplePos, 1.0);
        offset      = projection * offset;    // from view to clip-space
        offset.xyz /= offset.w;               // perspective divide
        offset.xyz  = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0
        float sampleDepth = texture(gPosition, offset.xy).z;

        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0) * rangeCheck;   
    }
    occlusion = 1.0 - (occlusion / kernelSize);
    FragColor = occlusion;
}