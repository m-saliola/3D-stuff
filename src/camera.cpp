#include "camera.h"

Camera::Camera(Transform transform,
               float fov, float aspect, 
               float near, float far) 
                  : m_Transform(transform), 
                    m_Fov(fov),
                    m_Aspect(aspect),
                    m_Near(near),
                    m_Far(far),
                    m_Proj(glm::perspective(glm::radians(fov), aspect, near, far)) {
    UpdateVectors();
    UpdateView();
}

void Camera::Translate(glm::vec3 translation) {
    SetPosition(m_Transform.position + translation);
}

void Camera::Rotate(glm::quat rotation) {
    SetRotation(m_Transform.rotation * rotation);
}
