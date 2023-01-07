#include "entity.h"

Cube::Cube(float side) {
    float hfSide = side / 2;
    float vertices[] = {
            -hfSide, hfSide, hfSide,
            -hfSide, -hfSide, hfSide,
            hfSide, hfSide, hfSide,
            hfSide, -hfSide, hfSide,
            -hfSide, hfSide, -hfSide,
            -hfSide, -hfSide, -hfSide,
            hfSide, hfSide, -hfSide,
            hfSide, -hfSide, -hfSide,
    };

    unsigned int indices[] = {
            0, 2, 3, 0, 3, 1,
            2, 6, 7, 2, 7, 3,
            6, 4, 5, 6, 5, 7,
            4, 0, 1, 4, 1, 5,
            0, 4, 6, 0, 6, 2,
            1, 5, 7, 1, 7, 3,
    };

    glGenBuffers(1, &_vbo);
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    // init material
    ka = glm::vec3(0.1f);
    kd = glm::vec3(0.8f);
    ks = glm::vec3(0.8f);
}

void Cube::draw() {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

glm::mat4 Entity::getModelMat() {
    glm::mat4 model(1.0f);
    return glm::translate(model, position);
}
