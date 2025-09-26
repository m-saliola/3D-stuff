#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <variant>

#include "shader.h"
#include "vendor/glm/glm.hpp"

struct MaterialParameter {
    std::string name;
    std::variant<
        int, unsigned int, float, 
        glm::vec2, glm::vec3, glm::vec4,
        glm::mat2, glm::mat3, glm::mat4
    > value;
};

class Material {
private:
    const Shader m_Shader;
    const std::vector<MaterialParameter> m_Params;

    std::vector<MaterialParameter> ParseMaterial(const std::string& filepath);
    Shader ParseMaterialShader(const std::string& filepath);

public:
    Material(const std::string& filepath);

    void Bind() const;
    void Unbind() const;

    inline const Shader& GetShader() const { return m_Shader; }
};