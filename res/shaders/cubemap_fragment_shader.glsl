#version 330 core

//Ins
in vec3 pass_uv;

//Outs
layout (location = 2) out vec3 out_color;

//Uniforms
uniform samplerCube skybox;


void main()
{
    out_color = texture(skybox, pass_uv).rgb;
}
