#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 vNormal;
out vec2 vTexCoord;
out vec3 fragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

void main() {
    gl_Position = project * view * model * vec4(aPosition, 1.0f);
    vNormal = normalize(mat3(transpose(inverse(model))) * aNormal);
    vTexCoord = aTexCoord;
    fragPos = vec3(model * vec4(aPosition, 1.0f));
}