#include "debug_visualizer.h"

#include "vertex_buffer_layout.h"

void DebugVisualizer::UpdateBuffers() const {
    m_Va.Bind();
    m_Va.Bind();
    m_Vb.SetData(m_Vertices.data(), m_Vertices.size() * sizeof(DebugVertex));
    m_Ib.SetData(m_Indices.data(), m_Indices.size());
}

DebugVisualizer::DebugVisualizer() : m_Va(), m_Vb(nullptr, 0), m_Ib(nullptr, 0), m_Shader("assets/shaders/debug.shader") {
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);

    m_Va.Bind();
    m_Vb.Bind();
    m_Va.AddBuffer(m_Vb, layout);
    m_Ib.Bind();

    UpdateBuffers();
}

void DebugVisualizer::Draw(const Renderer& renderer, const Camera& cam, float time) {
    UpdateBuffers();

    m_Shader.Bind();
    m_Shader.SetUniform<1, glm::mat4>("u_Model", glm::mat4(1));
    m_Shader.SetUniform<1, glm::mat4>("u_View", cam.GetViewMatrix());
    m_Shader.SetUniform<1, glm::mat4>("u_Proj", cam.GetProjectionMatrix());
    m_Shader.SetUniform<3, float>("u_ViewPos", cam.GetPosition().x, cam.GetPosition().y, cam.GetPosition().z);
    m_Shader.SetUniform<1, float>("u_Time", time);

    renderer.Draw(GL_LINES, m_Va, m_Ib, m_Shader);
}

void DebugVisualizer::AddLineToBuffers(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color) {
    m_Vertices.push_back(DebugVertex{pos1, color});
    m_Vertices.push_back(DebugVertex{pos2, color});
    m_Indices.push_back(m_Vertices.size() - 2);
    m_Indices.push_back(m_Vertices.size() - 1);
}

void DebugVisualizer::ClearBuffers() {
    m_Vertices.clear();
    m_Indices.clear();
}
