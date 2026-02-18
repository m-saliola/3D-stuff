#include "mesh.h"

#include "material.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::shared_ptr<Material> material) : m_Va(), 
        m_Vb(vertices.empty() ? nullptr : vertices.data(), vertices.size() * sizeof(Vertex)),
        m_Ib(indices.empty() ? nullptr : indices.data(), indices.size()), m_Material(material) {
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    m_Va.Bind();
    m_Vb.Bind();
    m_Va.AddBuffer(m_Vb, layout);
    m_Ib.Bind();
}
