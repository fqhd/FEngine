#version 330 core

//Ins
in vec3 pass_normal;
in vec3 pass_position;

//Outs
out vec4 out_color;

//Uniforms
uniform vec3 color;

void main(){

     out_color = vec4(color, 1.0);


}
