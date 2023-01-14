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

void Cube::draw() const {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

glm::mat4 Entity::getModelMat() const {
    return glm::translate(glm::mat4(1.0f), position) *
           glm::mat4_cast(rotation) *
           glm::scale(glm::mat4(1.0f), scale);
}

glm::vec3 Entity::getDefaultUp() {
    return {0.0f, 0.0f, 1.0f};
}

Sphere::Sphere(float radius, int sectors, int stacks) {
    std::vector<float> vertices;

    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = glm::pi<float>() * (0.5f - (float)i / stacks);
        float z, xy;
        z = radius * glm::sin(stackAngle);
        xy = radius * glm::cos(stackAngle);

        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = 2 * glm::pi<float>() / sectors * j;
            float x = xy * glm::cos(sectorAngle);
            float y = xy * glm::sin(sectorAngle);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            float s = (float)j / sectors;
            float t = (float)i / stacks;
            vertices.push_back(s);
            vertices.push_back(t);
        }
    }

    std::vector<unsigned int> indices;
    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k1 + 1);
                indices.push_back(k2);
            }

            if (i != stacks - 1) {
                indices.push_back(k1 + 1);
                indices.push_back(k2 + 1);
                indices.push_back(k2);
            }
        }
    }
    _count = indices.size();

    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
    glGenVertexArrays(1, &_vao);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void Sphere::draw() const {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, nullptr);
}

Sphere::~Sphere() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

Quad::Quad(float left, float right, float up, float bottom) {
    std::vector<float> vertices = {
            left, up, 0.0f, 1.0f,
            right, up, 1.0f, 1.0f,
            left, bottom, 0.0f, 0.0f,
            right, bottom, 1.0f, 0.0f
    };
    std::vector<unsigned int> indices = {
            0, 1, 2,
            1, 3, 2
    };

    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
    glGenVertexArrays(1, &_vao);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void Quad::draw() const {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

Quad::~Quad() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

Frustum::Frustum(float base, float top, float height, int sectors) {
    std::vector<float> vertices;

    for (int i = 0; i <= sectors; ++i) {
        float sectorAngle = 2 * glm::pi<float>() * i / sectors;
        vertices.push_back(top * glm::cos(sectorAngle));
        vertices.push_back(top * glm::sin(sectorAngle));
        vertices.push_back(height / 2);

        vertices.push_back(base * glm::cos(sectorAngle));
        vertices.push_back(base * glm::sin(sectorAngle));
        vertices.push_back(-height / 2);
    }
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(height / 2);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(-height / 2);

    std::vector<unsigned int> indices;
    for (int i = 0; i < sectors; ++i) {
        int k = i * 2;
        indices.push_back(k);
        indices.push_back(k + 2);
        indices.push_back(k + 1);

        indices.push_back(k + 1);
        indices.push_back(k + 2);
        indices.push_back(k + 3);

        // up
        indices.push_back(k);
        indices.push_back(2 * (sectors + 1));
        indices.push_back(k + 2);

        // down
        indices.push_back(k + 1);
        indices.push_back(k + 3);
        indices.push_back(2 * (sectors + 1) + 1);
    }
    _count = indices.size();

    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
    glGenVertexArrays(1, &_vao);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Frustum::draw() const {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, nullptr);
}

Frustum::~Frustum() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

Axis::Axis() {
    std::vector<float> vertices;
    vertices.push_back(-10000.0f);
    vertices.push_back(0.0f);
    vertices.push_back(10000.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(-10000.0f);
    vertices.push_back(0.0f);
    vertices.push_back(10000.0f);
    std::vector<int> axis;
    axis.push_back(0);
    axis.push_back(0);
    axis.push_back(1);
    axis.push_back(1);

    std::vector<unsigned int> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);


    glGenBuffers(2, _vbo);
    glGenBuffers(1, &_ebo);
    glGenVertexArrays(1, &_vao);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * axis.size(), axis.data(), GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, sizeof(int), nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Axis::draw() const {
    glBindVertexArray(_vao);
    glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, nullptr);
}

Axis::~Axis() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(2, _vbo);
    glDeleteBuffers(1, &_ebo);
}
