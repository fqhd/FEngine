#version 330 core

//Ins
in vec2 pass_uv;

//Outs
out vec4 out_color;

//Uniforms
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D albedoTexture;
uniform sampler2D ssaoTexture;
uniform vec2 inverseTextureSize;

//Constants
const float FXAA_SPAN_MAX = 1024.0;
const float FXAA_REDUCE_MIN = 1.0/128;
const float FXAA_REDUCE_MUL = 1.0/8.0;


void main() {

    // retrieve data from gbuffer
    vec3 fragmentPosition = texture2D(positionTexture, pass_uv).rgb;
    vec3 fragmentNormal = texture2D(normalTexture, pass_uv).rgb;
    float fragmentOcclusion = texture2D(ssaoTexture, pass_uv).r;

    vec2 texCoordOffset = inverseTextureSize.xy;

    vec3 luma = vec3(1.0, 1.0, 1.0);
    float lumaTL = dot(luma, texture2D(albedoTexture, pass_uv.xy + (vec2(-1.0, -1.0) * texCoordOffset)).xyz);
    float lumaTR = dot(luma, texture2D(albedoTexture, pass_uv.xy + (vec2(1.0, -1.0) * texCoordOffset)).xyz);
    float lumaBL = dot(luma, texture2D(albedoTexture, pass_uv.xy + (vec2(-1.0, 1.0) * texCoordOffset)).xyz);
    float lumaBR = dot(luma, texture2D(albedoTexture, pass_uv.xy + (vec2(1.0, 1.0) * texCoordOffset)).xyz);
    float lumaM  = dot(luma, texture2D(albedoTexture, pass_uv.xy).xyz);

    vec2 dir;
    dir.x = -((lumaTL + lumaTR) - (lumaBL + lumaBR));
    dir.y = ((lumaTL + lumaBL) - (lumaTR + lumaBR));

    float dirReduce = max((lumaTL + lumaTR + lumaBL + lumaBR) * (FXAA_REDUCE_MUL * 0.25), FXAA_REDUCE_MIN);
    float inverseDirAdjustment = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);

    dir = min(vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX),
         max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX), dir * inverseDirAdjustment)) * texCoordOffset;

    vec3 result1 = (1.0/2.0) * (
         texture2D(albedoTexture, pass_uv.xy + (dir * vec2(1.0/3.0 - 0.5))).xyz +
         texture2D(albedoTexture, pass_uv.xy + (dir * vec2(2.0/3.0 - 0.5))).xyz);

    vec3 result2 = result1 * (1.0/2.0) + (1.0/4.0) * (
         texture2D(albedoTexture, pass_uv.xy + (dir * vec2(0.0/3.0 - 0.5))).xyz +
         texture2D(albedoTexture, pass_uv.xy + (dir * vec2(3.0/3.0 - 0.5))).xyz);

    float lumaMin = min(lumaM, min(min(lumaTL, lumaTR), min(lumaBL, lumaBR)));
    float lumaMax = max(lumaM, max(max(lumaTL, lumaTR), max(lumaBL, lumaBR)));
    float lumaResult2 = dot(luma, result2);

    vec3 fragmentAlbedo;
    if(lumaResult2 < lumaMin || lumaResult2 > lumaMax){
     fragmentAlbedo = result1;
    }
    else{
     fragmentAlbedo = result2;
    }


    out_color = vec4(fragmentAlbedo * fragmentOcclusion, 1.0f);

}
