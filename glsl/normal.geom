#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

const float MAGNITUDE = 0.5;

uniform mat4 view;
uniform mat4 project;

vec3 GetNormal() {
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main()
{
    int i;
    for (i = 0; i < 3; ++i) {
        gl_Position = project * view * gl_in[i].gl_Position;
        EmitVertex();
        gl_Position = project * view * (gl_in[i].gl_Position + vec4(GetNormal(), 0.0) * MAGNITUDE);
        EmitVertex();
        EndPrimitive();
    }
}