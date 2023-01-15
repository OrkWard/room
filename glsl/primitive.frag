#version 330 core
in vec3 vNormal;
in vec3 fragPos;
in vec2 vTexCoord;
out vec4 color;

struct Ambient {
    vec3 color;
    float intensity;
};

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

struct Material {
    vec3 ka;
    vec3 kd;
    vec3 ks;
    float ns;
};

uniform Ambient ambient;
uniform Light light;
uniform Material material;
uniform vec3 viewPos;
uniform sampler2D aTex;

void main() {
    vec3 lightDir = normalize(fragPos - light.position);
    vec3 ambientLight = ambient.color * material.ka * ambient.intensity;

    vec3 diffLight = max(dot(vNormal, -lightDir), 0.0) * light.color * material.kd * light.intensity;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(lightDir, vNormal);
    vec3 specularLight = pow(max(dot(viewDir, reflectDir), 0.0f), material.ns) * light.color * material.ks * light.intensity;

    color = vec4(ambientLight + diffLight + specularLight, 1.0f) + texture(aTex, vTexCoord);
}
