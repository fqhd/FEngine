#version 330 core

//Ins
layout (location = 0) in vec3 in_position;

//Outs
out vec3 pass_uv;

//Uniforms
uniform mat4 projection;
uniform mat4 view;


void main() {

    pass_uv = in_position;
    vec4 pos = projection * view * vec4(in_position, 1.0);
    gl_Position = pos.xyww;

}
