#pragma once

#include <vector>
#include <memory>

#include "vertex.h"

class Material;

class Mesh {
private:
    VertexArray m_Va;
    VertexBuffer m_Vb;
    IndexBuffer m_Ib;
    std::shared_ptr<Material> m_Material;

public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::shared_ptr<Material> material);

    inline const VertexArray& GetVertexArray() const { return m_Va; }
    inline const VertexBuffer& GetVertexBuffer() const { return m_Vb; }
    inline const IndexBuffer& GetIndexBuffer() const { return m_Ib; }
    inline const std::shared_ptr<Material>& GetMaterial() const { return m_Material; }
};
