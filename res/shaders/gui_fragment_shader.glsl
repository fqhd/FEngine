#version 330 core

//In
in vec4 pass_color;
in vec2 pass_uv;

//Out
out vec4 out_color;

//Uniforms
uniform sampler2D ourTexture;

void main(){

     float transparency = texture(ourTexture, pass_uv).w;

     out_color = vec4(1.0, 1.0, 1.0, transparency);


}
