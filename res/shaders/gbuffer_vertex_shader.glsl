#version 330 core

//Ins
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_normal;

//Outs
out vec3 pass_position;
out vec3 pass_normal;

//Uniforms
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main(){

     gl_Position = projection * view * model * vec4(in_position, 1.0);

}
