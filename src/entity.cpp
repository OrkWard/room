#include "entity.h"

CreateEntity::CreateEntity(double xPos, double yPos, double width, double height) {
//    double vertices[] = {
//        convert2NDC(xPos, true), convert2NDC(yPos, false),
//        convert2NDC(xPos + width, true), convert2NDC(yPos, false),
//        convert2NDC(xPos + width, true), convert2NDC(yPos + height, false),
//        convert2NDC(xPos, true), convert2NDC(yPos, false),
//        convert2NDC(xPos + width, true), convert2NDC(yPos + height, false),
//        convert2NDC(xPos, true), convert2NDC(yPos + height, false),
//    };

    float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f,  0.5f,
    };
    glGenBuffers(1, &_vbo);
    glGenVertexArrays(1, &_vao);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(double) * 2, (void*)nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

CreateEntity::~CreateEntity() {
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}

void CreateEntity::draw() {
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
