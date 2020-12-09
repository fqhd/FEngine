#version 330 core

//Ins
in vec3 pass_position;
in vec3 pass_normal;

//Outs
layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec3 out_albedo;

//Uniforms
uniform vec3 color;


void main()
{

    out_position = pass_position;
    out_normal = normalize(pass_normal);
    out_albedo = color;

}
