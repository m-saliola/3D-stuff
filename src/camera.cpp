#include "camera.h"

Camera::Camera(const glm::vec3& pos, 
               const glm::vec3& rot,
               float fov, float aspect, 
               float near, float far) 
                  : m_Pos(pos), 
                    m_Rot(rot),
                    m_Proj(glm::perspective(glm::radians(fov), aspect, near, far)) {
    UpdateVectors();
    UpdateView();
}

void Camera::Translate(glm::vec3 translation) {
    SetPosition(glm::vec3(m_Pos + translation));
}

void Camera::Rotate(glm::vec3 rotation) {
    SetRotation(glm::vec3(m_Rot + rotation));
}