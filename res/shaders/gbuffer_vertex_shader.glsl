#version 330 core

//Ins
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in mat4 in_model;

//Outs
out vec3 pass_position;
out vec3 pass_normal;
out vec2 pass_uv;

//Uniforms
uniform mat4 projection;
uniform mat4 view;


void main(){

     vec4 viewPos = view * in_model * vec4(in_position, 1.0);
     pass_position = viewPos.xyz;

     mat3 normalMatrix = transpose(inverse(mat3(view * model)));
     pass_normal = normalMatrix * in_normal;

     pass_uv = in_uv;

     gl_Position = projection * viewPos;

}
