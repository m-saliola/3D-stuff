#include "vertex_array.h"
#include "vertex_buffer_layout.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    vb.Bind();
    const std::vector<VertexBufferElement>& elements = layout.GetElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.GetStride(), (const void*)(uintptr_t)offset);
        offset += elements[i].count * VertexBufferElement::GetSizeOfType(elements[i].type);
    }
}

void VertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}