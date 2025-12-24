#include "vendor/glm/glm.hpp"

struct RaycastData {
    float distance;
    glm::vec3 point;
    glm::vec3 normal;
    float u, v;
};

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;

    Ray(glm::vec3 origin, glm::vec3 direction);

    bool Raycast(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
    bool Raycast(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, RaycastData& data);
};
