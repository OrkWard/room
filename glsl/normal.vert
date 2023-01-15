#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 vNormal;
uniform mat4 model;

void main() {
    gl_Position = model * vec4(aPos, 1.0);
    vNormal = normalize(mat3(transpose(inverse(model))) * aNormal);
}