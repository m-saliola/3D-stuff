#pragma once

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class Camera {
private:
    glm::vec3 m_Pos;
    glm::vec3 m_Forward;
    glm::vec3 m_Up;
    glm::mat4 m_View;
    glm::mat4 m_Proj;

public:
    Camera(const glm::vec3& position = glm::vec3(0.0f), 
           const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), 
           float yaw = -90.0f, float pitch = 0.0f, 
           float fov = 45.0f, float aspectRatio = 1.0f, 
           float nearPlane = 0.01f, float farPlane = 1000.0f);

    inline glm::mat4 GetViewMatrix() const { return m_View; }
    inline glm::mat4 GetProjectionMatrix() const { return m_Proj; }

    inline glm::vec3 GetPosition() const { return m_Pos; }
    inline glm::vec3 GetForward() const { return m_Forward; }
    inline glm::vec3 GetUp() const { return m_Up; }

    inline void UpdateView() {
        m_View = glm::lookAt(m_Pos, m_Pos + m_Forward, m_Up);
    }

    inline void SetPosition(glm::vec3 pos) { 
        m_Pos = pos; 
        UpdateView();
    }

    inline void SetRotation(float yaw, float pitch) {
        m_Forward = glm::normalize(glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        ));
        UpdateView();
    }
};