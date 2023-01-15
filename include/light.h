#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct AmbientLight {
    float intensity = 0.2f;
    glm::vec3 color = { 1.0f, 1.0f, 1.0f };
};

struct DirectionalLight {
    float intensity = 1.0f;
    glm::vec3 direction = {1.0f, 1.0f, 1.0f};
    glm::vec3 color = {1.0f, 1.0f, 1.0f};
};

struct PointLight {
    glm::vec3 position = {.0f, .0f, .0f};
    glm::vec3 color = {1.0f, 1.0f, 1.0f};
    float intensity = 1.0f;
	float kc = 1.0f;
	float kl = 0.0f;
	float kq = 1.0f;
};