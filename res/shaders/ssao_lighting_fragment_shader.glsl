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

//Constants
const vec3 lightDir = vec3(-1, -1, -1);

void main() {

    // retrieve data from gbuffer
    vec3 fragmentPosition = texture(positionTexture, pass_uv).rgb;
    vec3 fragmentNormal = texture(normalTexture, pass_uv).rgb;
    vec3 fragmentAlbedo = texture(albedoTexture, pass_uv).rgb;
    float fragmentOcclusion = texture(ssaoTexture, pass_uv).r;

    out_color = vec4(fragmentAlbedo * fragmentOcclusion, 1.0f);


}
