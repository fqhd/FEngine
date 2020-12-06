#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

out vec3 pass_normal;
out vec3 pass_position;

uniform mat4 view;
uniform mat4 projection;


void main(){

     gl_Position = projection * view * vec4(in_position, 1.0);

     pass_normal = in_normal;
     pass_position = in_position;

}
