#version 330 core
#extension GL_ARB_gpu_shader5: require

layout(triangles, invocations = 3) in;
layout(triangle_strip, max_vertices = 3) out;
    
uniform mat4 lightSpaceMatrices[3];

flat in uint vID[];

flat out uint gID;

void main()
{
    for (int i = 0; i < 3; ++i)
    {
        gl_Position = lightSpaceMatrices[gl_InvocationID] * gl_in[i].gl_Position;
        gl_Layer = gl_InvocationID;
        gID = vID[i];
        EmitVertex();
    }
    EndPrimitive();
}  