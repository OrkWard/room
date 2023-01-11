#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Entity {
protected:
    unsigned int _vbo = 0;
    unsigned int _vao = 0;
    unsigned int _ebo = 0;
public:
    glm::vec3 position = glm::vec3(.0f);
    glm::quat rotation = glm::angleAxis(0.0f, glm::vec3(.0f, .0f, 1.0f));
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 ka = glm::vec3(0.1f);
    glm::vec3 kd = glm::vec3(1.0f);
    glm::vec3 ks = glm::vec3(1.0f);
    float ns = 32.0f;
public:
    glm::mat4 getModelMat() const;
    static glm::vec3 getDefaultUp();
    virtual void draw() = 0;
};

class Cube: public Entity {
public:
    explicit Cube(float side);
    void draw() override;
};


class Sphere: public Entity {
private:
    long _count;
public:
    explicit Sphere(float radius, int sectors, int stacks);
    void draw() override;
};