#pragma once

#include <vector>

#include "glad/glad.h"
#include "renderer.h"
#include "vertex.h"
#include "material.h"
#include "camera.h"

#include "vendor/glm/glm.hpp"

class Model;

struct Batch {
    unsigned int material;
    unsigned int vertexOffset;
    unsigned int indexOffset;
    unsigned int indexCount;
};

class Batcher {
private:
    VertexArray m_Va;
    VertexBuffer m_Vb;
    IndexBuffer m_Ib;

    std::vector<Batch> m_Batches;
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;

    std::vector<Material> m_Materials;
    std::unordered_map<std::string, unsigned int> m_MaterialPaths;

    void UpdateBuffers() const;

public:
    Batcher();

    inline const std::vector<Batch>& GetBatches() const { return m_Batches; }
    inline const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
    inline const std::vector<unsigned int>& GetIndices() const { return m_Indices; }

    void AddModel(const Model& model);

    unsigned int RegisterMaterial(const Material& material);

    void Draw(const Renderer& renderer, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const Camera& cam) const;
};