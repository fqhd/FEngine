#version 330 core

//In
layout (location = 0) in vec2 in_position;
layout (location = 1) in vec4 in_color;
layout (location = 2) in vec2 in_uv;

//Out
out vec4 pass_color;
out vec2 pass_uv;

//Uniforms
uniform mat4 matrix;

void main() {

    gl_Position = matrix * vec4(in_position, 0.0, 1.0);


    pass_color = in_color;
    pass_uv = vec2(vertexUV.x, 1.0 - vertexUV.y);

}
