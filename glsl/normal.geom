#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

const float MAGNITUDE = 0.5;

in vec3 vNormal[];

uniform mat4 view;
uniform mat4 project;

void main()
{
    int i;
    for (i = 0; i < 3; ++i) {
        gl_Position = project * view * gl_in[i].gl_Position;
        EmitVertex();
        gl_Position = project * view * (gl_in[i].gl_Position + vec4(vNormal[i], 0.0) * MAGNITUDE);
        EmitVertex();
        EndPrimitive();
    }
}