LOAD_AS_STRING(
layout (location = 0) in vec3 position;

out vec3 textureCoords;

uniform mat4 projection;
uniform mat4 view;

void main(){
    textureCoords = position;
    vec4 pos = projection * view * vec4(position, 1.0);
    gl_Position = pos.xyww;
}
)