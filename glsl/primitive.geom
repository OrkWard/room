#version 330
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 vTexCoord[];
out vec3 normal;
out vec2 gTexCoord;
out vec3 fragPos;

uniform mat4 view;
uniform mat4 project;

vec3 GetNormal() {
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {
    normal = GetNormal();

    int i;
    for (i = 0; i < 3; ++i) {
        gl_Position = project * view * gl_in[i].gl_Position;
        fragPos = gl_in[i].gl_Position.xyz / gl_in[i].gl_Position.w;
        gTexCoord = vTexCoord[i];
        EmitVertex();
    }
    EndPrimitive();
}