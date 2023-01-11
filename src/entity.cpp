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
            1, 7, 5, 1, 3, 7,
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
}

void Cube::draw() {
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    glDisable(GL_DEPTH_TEST);
}

glm::mat4 Entity::getModelMat() const {
    return glm::translate(glm::mat4(1.0f), position) *
           glm::mat4_cast(rotation) *
           glm::scale(glm::mat4(1.0f), scale);
}

glm::vec3 Entity::getDefaultUp() {
    return {0.0f, 0.0f, 1.0f};
}
