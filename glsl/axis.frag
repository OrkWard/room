#version 330 core
flat in int vAxis;

out vec4 color;

void main() {
    if (vAxis == 1) {
        color = vec4(.0f, 1.f, .0f, 1.f);
    }
    else {
        color = vec4(1.f, .0f, .0f, 1.f);
    }
}