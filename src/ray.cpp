#include "ray.h"

Ray::Ray(glm::vec3 origin, glm::vec3 direction) : origin(origin), direction(glm::normalize(direction)) { }

bool Ray::Raycast(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
    glm::vec3 v0v1 = v1 - v0;
    glm::vec3 v0v2 = v2 - v0;

    glm::vec3 P = glm::cross(direction, v0v2);
    float det = glm::dot(v0v1, P);

    if (fabs(det) < 1e-6f) return false;

    glm::vec3 T = origin - v0;
    float u = glm::dot(T, P) / det;
    if (u < 0.0f || u > 1.0f) return false;

    glm::vec3 Q = glm::cross(T, v0v1);
    float v = glm::dot(direction, Q) / det;
    if (v < 0.0f || u + v > 1.0f) return false;

    float t = glm::dot(v0v2, Q) / det;
    if (t < 0.0f) return false;

    return true;
}

bool Ray::Raycast(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, RaycastData& data) {
    glm::vec3 v0v1 = v1 - v0;
    glm::vec3 v0v2 = v2 - v0;

    glm::vec3 P = glm::cross(direction, v0v2);
    float det = glm::dot(v0v1, P);

    if (fabs(det) < 1e-6f) return false;

    glm::vec3 T = origin - v0;
    float u = glm::dot(T, P) / det;
    if (u < 0.0f || u > 1.0f) return false;

    glm::vec3 Q = glm::cross(T, v0v1);
    float v = glm::dot(direction, Q) / det;
    if (v < 0.0f || u + v > 1.0f) return false;

    float t = glm::dot(v0v2, Q) / det;
    if (t < 0.0f) return false;

    data = RaycastData{
        t,
        origin + t * direction,
        glm::normalize((glm::dot(glm::cross(v0v1, v0v2), direction) > 0) ? -glm::cross(v0v1, v0v2) : glm::cross(v0v1, v0v2)),
        u,
        v
    };

    return true;
}

