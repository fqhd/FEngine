#version 330 core

//Ins
in vec3 pass_position;
in vec3 pass_normal;
in vec2 pass_uv;

//Outs
layout (location = 0) out vec4 out_position;
layout (location = 1) out vec4 out_normal;
layout (location = 2) out vec4 out_albedo;

//Uniforms
uniform sampler2D ourTexture;

void main() {

    out_position = vec4(pass_position, 1.0f);
    out_normal = vec4(normalize(pass_normal), 1.0f);
    out_albedo = vec4(texture2D(ourTexture, pass_uv).rgb, 1.0f);

}
