#pragma once

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    inline glm::mat4 GenerateModelMatrix() const { return glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation) * glm::scale(glm::mat4(1.0f), scale); }
};
