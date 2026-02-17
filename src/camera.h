#pragma once

#include "transform.h"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtx/euler_angles.hpp" 

class Camera {
private:
    // glm::vec3 m_Pos;
    // glm::vec3 m_Rot;
    Transform m_Transform;

    float m_Fov;
    float m_Aspect;
    float m_Near;
    float m_Far;
    glm::vec3 m_Forward;
    glm::vec3 m_Right;
    glm::vec3 m_Up;
    glm::mat4 m_View;
    glm::mat4 m_Proj;

    void UpdateVectors() {
        m_Forward = glm::normalize(glm::vec3(cos(glm::radians(m_Transform.rotation.y)) * cos(glm::radians(m_Transform.rotation.x)), sin(glm::radians(m_Transform.rotation.x)), sin(glm::radians(m_Transform.rotation.y)) * cos(glm::radians(m_Transform.rotation.x))));
        m_Right = glm::normalize(glm::cross(m_Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
        m_Up = glm::normalize(glm::cross(m_Right, m_Forward));

        if (m_Transform.rotation.z != 0.0f) {
            glm::mat4 rollRot = glm::rotate(glm::mat4(1.0f), glm::radians(m_Transform.rotation.z), m_Forward);
            m_Right = glm::normalize(glm::vec3(rollRot * glm::vec4(m_Right, 0.0f)));
            m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
        }

        UpdateView();
    }

public:
    Camera(const glm::vec3& position = glm::vec3(0.0f),
           const glm::vec3& rot = glm::vec3(0.0f, -90.0f, 0.0f),
           float fov = 45.0f, float aspect = 1.0f,
           float near = 0.01f, float far = 1000.0f);

    inline glm::mat4 GetViewMatrix() const { return m_View; }
    inline glm::mat4 GetProjectionMatrix() const { return m_Proj; }

    inline glm::vec3 GetPosition() const { return m_Transform.position; }
    inline glm::vec3 GetRotation() const { return m_Transform.rotation; }

    inline float GetFov() const { return m_Fov; }
    inline float GetAspect() const { return m_Aspect; }
    inline float GetNearPlane() const { return m_Near; }
    inline float GetFarPlane() const { return m_Far; }

    inline glm::vec3 GetForward() const { return m_Forward; }
    inline glm::vec3 GetRight() const { return m_Right; }
    inline glm::vec3 GetUp() const { return m_Up; }

    inline void UpdateView() {
        m_View = glm::lookAt(m_Transform.position, m_Transform.position + m_Forward, m_Up);
    }

    inline void SetPosition(glm::vec3 pos) { 
        m_Transform.position = pos;

        UpdateVectors();
    }

    inline void SetRotation(glm::vec3 rot) {
        m_Transform.rotation = rot;

        UpdateVectors();
    }

    void Translate(glm::vec3 translation);
    void Rotate(glm::vec3 rotation);
};
