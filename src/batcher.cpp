#include "batcher.h"
#include "vertex_buffer_layout.h"

#include "model.h"

#include <iostream>

void Batcher::UpdateBuffers() const {
    m_Va.Bind();
    m_Va.Bind();
    m_Vb.SetData(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
    m_Ib.SetData(m_Indices.data(), m_Indices.size());
}

Batcher::Batcher() : m_Va(), m_Vb(nullptr, 0), m_Ib(nullptr, 0) {
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    m_Va.Bind();
    m_Vb.Bind();
    m_Va.AddBuffer(m_Vb, layout);
    m_Ib.Bind();

    UpdateBuffers();
}

void Batcher::Draw(const Renderer& renderer, const glm::mat4& model, const Camera& cam, float time) const {
    UpdateBuffers();

    for (const Batch& batch : m_Batches) {
        const Shader& sh = *m_Materials[batch.material].GetShader();

        sh.Bind();
        sh.SetUniform<1, glm::mat4>("u_Model", model);
        sh.SetUniform<1, glm::mat4>("u_View", cam.GetViewMatrix());
        sh.SetUniform<1, glm::mat4>("u_Proj", cam.GetProjectionMatrix());
        sh.SetUniform<3, float>("u_ViewPos", cam.GetPosition().x, cam.GetPosition().y, cam.GetPosition().z);
        sh.SetUniform<1, float>("u_Time", time);

        renderer.Draw(m_Va, m_Ib, m_Materials[batch.material], batch.indexOffset, batch.indexCount);
    }
}

void Batcher::AddModel(const Model& model) {
    for (const auto& mesh : model.GetMeshes()) {
        unsigned int vertexOffset = m_Vertices.size();
        m_Vertices.insert(m_Vertices.end(), mesh.vertices.begin(), mesh.vertices.end());
        
        unsigned int indexOffset = m_Indices.size();
        // m_Indices.insert(m_Indices.end(), mesh.indices.begin(), mesh.indices.end());
        for (unsigned int index : mesh.indices) 
            m_Indices.push_back(index + vertexOffset);

        bool found = false;
        for (Batch& batch : m_Batches) 
            if (batch.material == mesh.material) {
                batch.indexCount += mesh.indices.size();
                found = true;
                break;
            }
        
        if (!found)
            m_Batches.push_back(Batch{
                mesh.material, 
                vertexOffset, 
                indexOffset, 
                static_cast<unsigned int>(mesh.indices.size())
            });
    }
}

unsigned int Batcher::RegisterMaterial(const Material& material) {
    if (m_MaterialPaths.find(material.GetPath()) != m_MaterialPaths.end())
        return m_MaterialPaths[material.GetPath()];

    m_Materials.push_back(material);
    unsigned int id = static_cast<unsigned int>(m_Materials.size() - 1);
    m_MaterialPaths[material.GetPath()] = id;
    return id;
}