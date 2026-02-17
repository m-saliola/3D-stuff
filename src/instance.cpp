#include "instance.h"

Instance::Instance(Model model, Transform transform = Transform{glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)}) { }

void Instance::Draw(const Renderer& renderer, const Camera& cam, float time) { // i think this function is done, test it so that we may be rid of the cursed batcher class!
    for (Mesh mesh : m_Model.GetMeshes()) {
        VertexArray va = mesh.GetVertexArray();
        IndexBuffer ib = mesh.GetIndexBuffer();
        // VertexBuffer vb = mesh.GetVertexBuffer();

        const Shader& sh = *(*mesh.GetMaterial()).GetShader();

        sh.Bind();
        sh.SetUniform<1, glm::mat4>("u_Model", m_Transform.GenerateModelMatrix());
        sh.SetUniform<1, glm::mat4>("u_View", cam.GetViewMatrix());
        sh.SetUniform<1, glm::mat4>("u_Proj", cam.GetProjectionMatrix());
        sh.SetUniform<3, float>("u_ViewPos", cam.GetPosition().x, cam.GetPosition().y, cam.GetPosition().z);
        sh.SetUniform<1, float>("u_Time", time);

        renderer.Draw(GL_TRIANGLES, va, ib, m_Materials[batch.material], batch.indexOffset, batch.indexCount);
    }
}
