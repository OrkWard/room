#version 330 core
in vec2 vTexCoord;

out vec4 color;

uniform sampler2D aTex;

void main() {
    color = texture(aTex, vTexCoord);
}