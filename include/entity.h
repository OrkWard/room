#pragma once

#include <string>
#include <glad/glad.h>
#include "transform.h"

class Entity {
protected:
    unsigned int _vbo = 0;
    unsigned int _vao = 0;
    unsigned int _ebo = 0;
public:
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
public:
    glm::mat4 getModelMat();
    virtual void draw() = 0;
};

class Cube: public Entity{
public:
    glm::vec3 ka;
    glm::vec3 kd;
    glm::vec3 ks;
    float ns = 32.0f;
public:
    Cube(float side);
    void draw() override;
};