#include "camera.h"

Camera::Camera(const glm::vec3& pos, 
               const glm::vec3& rot,
               float fov, float aspect, 
               float near, float far) 
                  : m_Transform(Transform{pos, rot, glm::vec3(0.0f)}), 
                    m_Fov(fov),
                    m_Aspect(aspect),
                    m_Near(near),
                    m_Far(far),
                    m_Proj(glm::perspective(glm::radians(fov), aspect, near, far)) {
    UpdateVectors();
    UpdateView();
}

void Camera::Translate(glm::vec3 translation) {
    SetPosition(glm::vec3(m_Transform.position + translation));
}

void Camera::Rotate(glm::vec3 rotation) {
    SetRotation(glm::vec3(m_Transform.rotation + rotation));
}
