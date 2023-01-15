#version 330 core
layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;
uniform mat4 model;

void main() {
    gl_Position = model * vec4(Position, 1.0f);
    vTexCoord = aTexCoord;
}