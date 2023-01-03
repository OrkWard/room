#version 330 core
in vec3 normal;
out vec4 color;

struct Ambient {
    vec3 color;
    float intensity;
};

struct Light {
    vec3 direction;
    vec3 color;
    float intensity;
};

struct Material {
    vec3 ka;
    vec3 kd;
//    vec3 ks;
//    float ns;
};

uniform Ambient ambient;
uniform Light light;
uniform Material material;

void main() {
    vec3 ambientLight = ambient.color * material.ka * ambient.intensity;

    vec3 diffLight = max(dot(normal, normalize(-light.direction)), 0.0) * light.color * material.kd * light.intensity;

    color = vec4(ambientLight + diffLight, 0.0f);
}
