#version 330 core

//Ins
in vec3 pass_normal;
in vec3 pass_position;

//Outs
out vec4 out_color;

//Uniforms
uniform vec3 color;

//Constants
const vec3 lightPosition = vec3(10, -10, 10);

void main(){

     out_color = vec4(color * clamp(dot(-normalize(vec3(0.3, -3, 0.5)), normalize(pass_normal)), 0.2, 1.0), 1.0);

}
