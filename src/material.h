#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <variant>
#include <memory>

#include "shader.h"
#include "mesh.h"
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
    const std::string m_Filepath;
    const std::shared_ptr<Shader> m_Shader;
    const std::vector<MaterialParameter> m_Params;
    std::vector<const Mesh*> m_Users;

    std::vector<MaterialParameter> ParseMaterial(const std::string& filepath);
    std::shared_ptr<Shader> ParseMaterialShader(const std::string& filepath);

public:
    Material(const std::string& filepath);
    ~Material();

    void Bind() const;
    void Unbind() const;

    void SetUniforms() const;

    inline const std::shared_ptr<Shader> GetShader() const { return m_Shader; }
    inline const std::string& GetPath() const { return m_Filepath; }
};