#include "camera.h"

Camera::Camera(const glm::vec3& pos, 
               const glm::vec3& up, 
               float yaw, float pitch, 
               float fov, float aspect, 
               float near, float far) 
                  : m_Pos(pos), 
                    m_Up(up),
                    m_Forward(glm::normalize(glm::vec3(cos(
                        glm::radians(yaw)) * cos(glm::radians(pitch)), 
                        sin(glm::radians(pitch)), 
                        sin(glm::radians(yaw)) * cos(glm::radians(pitch))))),
                    m_View(glm::lookAt(pos, pos + m_Forward, m_Up)),
                    m_Proj(glm::perspective(fov, aspect, near, far)) { }