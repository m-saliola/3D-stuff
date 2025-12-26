#include "renderer.h"

void Renderer::Draw(GLenum mode, const VertexArray& va,const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(mode, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(GLenum mode, const VertexArray& va,const IndexBuffer& ib, const Material& material) const {
    material.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(mode, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(GLenum mode, const VertexArray& va,const IndexBuffer& ib, const Shader& shader, unsigned int indexOffset, unsigned int indexCount) const {
    shader.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(mode, indexCount, GL_UNSIGNED_INT, (void*)(indexOffset * sizeof(unsigned int)));
}

void Renderer::Draw(GLenum mode, const VertexArray& va,const IndexBuffer& ib, const Material& material, unsigned int indexOffset, unsigned int indexCount) const {
    material.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(mode, indexCount, GL_UNSIGNED_INT, (void*)(indexOffset * sizeof(unsigned int)));
}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearColor(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}
