#version 330 core

//Ins
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

//Outs
out vec3 pass_position;
out vec3 pass_normal;

//Uniforms
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main(){

     vec4 viewPos = view * model * vec4(in_position, 1.0);
     pass_position = viewPos.xyz;

     mat3 normalMatrix = transpose(inverse(mat3(view * model)));
     pass_normal = normalMatrix * in_normal;

     gl_Position = projection * viewPos;

}
