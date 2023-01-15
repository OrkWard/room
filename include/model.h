#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>

#include "bounding_box.h"
#include "vertex.h"
#include "entity.h"

class Model: public Entity{
public:
    explicit Model(const std::string& filepath);

    Model(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    Model(Model&& rhs) noexcept;

    ~Model() override;

    size_t getVertexCount() const;

    size_t getFaceCount() const;

    void draw() const override;

    const std::vector<uint32_t>& getIndices() const { return _indices; }
    const std::vector<Vertex>& getVertices() const { return _vertices; }
    const Vertex& getVertex(int i) const { return _vertices[i]; }

protected:
    // vertices of the table represented in model's own coordinate
    std::vector<Vertex> _vertices;
    std::vector<uint32_t> _indices;

    // opengl objects
    GLuint _boxVao = 0;
    GLuint _boxVbo = 0;
    GLuint _boxEbo = 0;

    void initGLResources();

    void cleanup();
};