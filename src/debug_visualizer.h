#pragma once

#include <glad/glad.h>

#include <vector>

#include "renderer.h"
#include "camera.h"

#include "vendor/glm/glm.hpp"

struct DebugVertex {
    glm::vec3 pos;
    glm::vec3 color;
};

class DebugVisualizer {
private:
    VertexArray m_Va;
    VertexBuffer m_Vb;
    IndexBuffer m_Ib;

    const Shader m_Shader;

    std::vector<DebugVertex> m_Vertices;
    std::vector<unsigned int> m_Indices;

    void UpdateBuffers() const;

public:
    DebugVisualizer();

    void AddLineToBuffers(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color);

    void Draw(const Renderer& renderer, const Camera& cam, float time);

    void ClearBuffers();
};
