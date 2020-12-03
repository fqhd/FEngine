#version 330 core

//In
in vec4 pass_color;
in vec2 pass_uv;

//Out
out vec4 out_color;

//Uniforms
uniform sampler2D ourTexture;

void main(){

     out_color = texture2D(ourTexture, pass_uv);

     out_color *= pass_color;
     out_color.w = pass_color.w;

}
