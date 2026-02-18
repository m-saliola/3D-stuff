#pragma once

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/quaternion.hpp"

struct Transform {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    inline glm::mat4 GenerateModelMatrix() const { return glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation) * glm::scale(glm::mat4(1.0f), scale); }
};
