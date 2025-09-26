#include "renderer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount() * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearColor(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}