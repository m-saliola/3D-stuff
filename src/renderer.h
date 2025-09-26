#pragma once

#include <glad/glad.h>

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Renderer {
public:
    void Draw(const VertexArray& VAO, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
    void ClearColor(float r, float g, float b, float a) const;
};