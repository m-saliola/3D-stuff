#pragma once

#include <glad/glad.h>

#include <iostream>

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"
#include "material.h"

inline void PrintGLError(const char* location) {
    GLenum e;
    while ((e = glGetError()) != GL_NO_ERROR) {
        std::cout << "GLERR at " << location << " : 0x" << std::hex << e << std::dec << " (" << e << ")\n";
    }
}

class Renderer {
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Material& material) const;

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int indexOffset, unsigned int indexCount) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Material& material, unsigned int indexOffset, unsigned int indexCount) const;

    void Clear() const;
    void ClearColor(float r, float g, float b, float a) const;
};