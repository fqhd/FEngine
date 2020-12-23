#version 330 core

//Ins
in vec3 pass_uv;

//Outs
layout (location = 2) out vec4 out_color;

//Uniforms
uniform samplerCube skybox;

void main()
{
    out_color = texture3D(skybox, pass_uv);
}
