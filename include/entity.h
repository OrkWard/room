#pragma once

#include <string>
#include <glad/glad.h>
#include "utility.h"

class Entity {
protected:
    unsigned int _vbo = 0;
    unsigned int _vao = 0;
    unsigned int _ebo = 0;
public:
    virtual void draw() = 0;
};

class Cube: public Entity{
public:
    Cube(float side);
    void draw() override;
};