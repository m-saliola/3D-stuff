#pragma once

#include <memory>

#include "model"
#include "transform"

class Instance {
private:
    std::shared_ptr<Model> m_Model;
    Transform m_Transform;

public:
    Instance(std::shared_ptr<Model> model, Transform transform);

    inline const std::shared_ptr<Model>& GetModel() const { return m_Model; }

    inline const Transform& GetTransform() const { return m_Transform; }
    inline Transform& GetTransform() { return m_Transform; }

    void Draw(const Renderer& renderer, const Camera& cam, float time);
}
