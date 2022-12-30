#pragma once

#include <string>
#include <glad/glad.h>
#include "utility.h"

class CreateEntity {
private:
    unsigned int _vbo = 0;
    unsigned int _vao = 0;
public:
    CreateEntity(double xPos, double yPos, double width, double height);
    ~CreateEntity();
    void draw();
};