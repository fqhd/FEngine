#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_normal;

out vec2 pass_uv;
out vec3 pass_normal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;


void main(){
     gl_Position = projection * view * model * vec4(in_position, 1.0);

     pass_uv = in_uv;
     pass_normal = in_normal;
     
}
