#include "instance.h"

#include "camera.h"
#include "renderer.h"

Instance::Instance(std::shared_ptr<Model> model) : m_Model(model), m_Transform(Transform{glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)}) { }
Instance::Instance(std::shared_ptr<Model> model, Transform transform) : m_Model(model), m_Transform(transform) { }

void Instance::Draw(const Renderer& renderer, const Camera& cam, float time) { // i think this function is done, test it so that we may be rid of the cursed batcher class!
    for (const Mesh& mesh : m_Model->GetMeshes()) {
        const VertexArray& va = mesh.GetVertexArray();
        const IndexBuffer& ib = mesh.GetIndexBuffer();

        const Material&  material = *mesh.GetMaterial();
        const Shader& shader = *material.GetShader();

        shader.Bind();
        shader.SetUniform<1, glm::mat4>("u_Model", m_Transform.GenerateModelMatrix());
        shader.SetUniform<1, glm::mat4>("u_View", cam.GetViewMatrix());
        shader.SetUniform<1, glm::mat4>("u_Proj", cam.GetProjectionMatrix());
        shader.SetUniform<3, float>("u_ViewPos", cam.GetPosition().x, cam.GetPosition().y, cam.GetPosition().z);
        shader.SetUniform<1, float>("u_Time", time);

        renderer.Draw(GL_TRIANGLES, va, ib, material);
    }
}
