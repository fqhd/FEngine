LOAD_AS_STRING(
uniform sampler2D ourTexture;
in vec2 vUV;
in vec2 v_rgbNW;
in vec2 v_rgbNE;
in vec2 v_rgbSW;
in vec2 v_rgbSE;
in vec2 v_rgbM;
uniform ivec2 iResolution;
out vec4 outColor;

const float FXAA_REDUCE_MIN = (1.0/ 128.0);
const float FXAA_REDUCE_MUL = (1.0 / 8.0);
const float FXAA_SPAN_MAX = 8.0;

vec4 fxaa() {
    vec2 fragCoord = vUV * iResolution;
    vec4 color;
    mediump vec2 inverseVP = vec2(1.0 / iResolution.x, 1.0 / iResolution.y);
    vec3 rgbNW = texture(ourTexture, v_rgbNW).xyz;
    vec3 rgbNE = texture(ourTexture, v_rgbNE).xyz;
    vec3 rgbSW = texture(ourTexture, v_rgbSW).xyz;
    vec3 rgbSE = texture(ourTexture, v_rgbSE).xyz;
    vec4 texColor = texture(ourTexture, v_rgbM);
    vec3 rgbM  = texColor.xyz;
    vec3 luma = vec3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM  = dot(rgbM,  luma);
    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));
    
    mediump vec2 dir;
    dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
    
    float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) *
                          (0.25 * FXAA_REDUCE_MUL), FXAA_REDUCE_MIN);
    
    float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);
    dir = min(vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX),
              max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
              dir * rcpDirMin)) * inverseVP;
    
    vec3 rgbA = 0.5 * (
        texture(ourTexture, fragCoord * inverseVP + dir * (1.0 / 3.0 - 0.5)).xyz +
        texture(ourTexture, fragCoord * inverseVP + dir * (2.0 / 3.0 - 0.5)).xyz);
    vec3 rgbB = rgbA * 0.5 + 0.25 * (
        texture(ourTexture, fragCoord * inverseVP + dir * -0.5).xyz +
        texture(ourTexture, fragCoord * inverseVP + dir * 0.5).xyz);

    float lumaB = dot(rgbB, luma);
    if ((lumaB < lumaMin) || (lumaB > lumaMax))
        color = vec4(rgbA, texColor.a);
    else
        color = vec4(rgbB, texColor.a);
    return color;
}

void main(){
    outColor = fxaa();
}
)