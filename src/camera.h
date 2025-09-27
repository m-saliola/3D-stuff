#pragma once

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtx/euler_angles.hpp" 

class Camera {
private:
    glm::vec3 m_Pos;
    glm::vec3 m_Rot;
    glm::vec3 m_Forward;
    glm::vec3 m_Right;
    glm::vec3 m_Up;
    glm::mat4 m_View;
    glm::mat4 m_Proj;

    void UpdateVectors() {
        m_Forward = glm::normalize(glm::vec3(cos(glm::radians(m_Rot.x)) * cos(glm::radians(m_Rot.y)), sin(glm::radians(m_Rot.y)), sin(glm::radians(m_Rot.x)) * cos(glm::radians(m_Rot.y))));
        m_Right = glm::normalize(glm::cross(m_Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
        m_Up = glm::normalize(glm::cross(m_Right, m_Forward));

        if (m_Rot.z != 0.0f) {
            glm::mat4 rollRot = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rot.z), m_Forward);
            m_Right = glm::normalize(glm::vec3(rollRot * glm::vec4(m_Right, 0.0f)));
            m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
        }

        UpdateView();
    }

public:
    Camera(const glm::vec3& position = glm::vec3(0.0f), 
           const glm::vec3& rot = glm::vec3(-90.0f, 0.0f, 0.0f), 
           float fov = 45.0f, float aspectRatio = 1.0f, 
           float nearPlane = 0.01f, float farPlane = 1000.0f);

    inline glm::mat4 GetViewMatrix() const { return m_View; }
    inline glm::mat4 GetProjectionMatrix() const { return m_Proj; }

    inline glm::vec3 GetPosition() const { return m_Pos; }
    inline glm::vec3 GetRotation() const { return m_Rot; }

    inline glm::vec3 GetForward() const { return m_Forward; }
    inline glm::vec3 GetRight() const { return m_Right; }
    inline glm::vec3 GetUp() const { return m_Up; }

    inline void UpdateView() {
        m_View = glm::lookAt(m_Pos, m_Pos + m_Forward, m_Up);
    }

    inline void SetPosition(glm::vec3 pos) { 
        m_Pos = pos; 

        UpdateVectors();
    }

    inline void SetRotation(glm::vec3 rot) {
        m_Rot = rot;

        UpdateVectors();
    }

    void Translate(glm::vec3 translation);
    void Rotate(glm::vec3 rotation);
};