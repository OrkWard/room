#version 330 core
layout (location = 0) in vec2 aPosition;
layout (location = 1) in int aAxis;

uniform mat4 view;
uniform mat4 project;

flat out int vAxis;

void main() {
    gl_Position = project * view * vec4(aPosition, 0.0f, 1.0f);
    vAxis = aAxis;
}