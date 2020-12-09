#version 330 core

//Ins
in vec2 pass_uv;

//Outs
out vec4 out_color;

//Uniforms
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D albedoTexture;


void main(){

     out_color = texture(albedoTexture, pass_uv);

}
