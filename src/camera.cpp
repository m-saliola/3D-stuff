#include "camera.h"

Camera::Camera(const glm::vec3& pos, 
               const glm::vec3& rot,
               float fov, float aspect, 
               float near, float far) 
                  : m_Pos(pos), 
                    m_Rot(rot),
                    m_Proj(glm::perspective(fov, aspect, near, far)) {
    UpdateVectors();
    UpdateView();
}