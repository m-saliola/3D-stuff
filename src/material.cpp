#include "material.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

Material::Material(const std::string& filepath) : m_Filepath(filepath), m_Shader(ParseMaterialShader(filepath)), m_Params(ParseMaterial(filepath)) { 
    Bind();
}

Material::~Material() {
    m_Users.clear();
}

void Material::Bind() const { 
    m_Shader->Bind();
    SetUniforms();
}

void Material::Unbind() const { 
    m_Shader->Unbind();
}

void Material::SetUniforms() const {
    for (const auto& param : m_Params) {
        std::visit([&](auto&& value) {
            using T = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<T, int>) {
                m_Shader->SetUniform<1, int>(param.name, value);
            } else if constexpr (std::is_same_v<T, unsigned int>) {
                m_Shader->SetUniform<1, unsigned int>(param.name, value);
            } else if constexpr (std::is_same_v<T, float>) {
                m_Shader->SetUniform<1, float>(param.name, value);
            } else if constexpr (std::is_same_v<T, glm::vec2>) {
                m_Shader->SetUniform<2, float>(param.name, value.x, value.y);
            } else if constexpr (std::is_same_v<T, glm::vec3>) {
                m_Shader->SetUniform<3, float>(param.name, value.x, value.y, value.z);
            } else if constexpr (std::is_same_v<T, glm::vec4>) {
                m_Shader->SetUniform<4, float>(param.name, value.x, value.y, value.z, value.w);
            } else if constexpr (std::is_same_v<T, glm::mat2>) {
                m_Shader->SetUniform<1, glm::mat2>(param.name, value);
            } else if constexpr (std::is_same_v<T, glm::mat3>) {
                m_Shader->SetUniform<1, glm::mat3>(param.name, value);
            } else if constexpr (std::is_same_v<T, glm::mat4>) {
                m_Shader->SetUniform<1, glm::mat4>(param.name, value);
            }
        }, param.value);
    }
}

std::vector<MaterialParameter> Material::ParseMaterial(const std::string& filepath) {
    std::ifstream in(filepath);

    if (!in.is_open()) {
        std::cout << "Failed to open material: " << filepath << std::endl;
        return {};
    }

    std::vector<MaterialParameter> params;

    std::string line;
    std::string prefix;
    while (getline(in, line)) {
        std::istringstream iss(line);
        iss >> prefix;

        std::string name;
        if (prefix == "int") {
            int value;
            iss >> name >> value;
            params.push_back({name, value});
        } else if (prefix == "float") {
            float value;
            iss >> name >> value;
            params.push_back({name, value});
        } else if (prefix == "vec2") {
            glm::vec2 value;
            iss >> name >> value.x >> value.y;
            params.push_back({name, value});
        } else if (prefix == "vec3") {
            glm::vec3 value;
            iss >> name >> value.x >> value.y >> value.z;
            params.push_back({name, value});
        } else if (prefix == "vec4") {
            glm::vec4 value;
            iss >> name >> value.x >> value.y >> value.z >> value.w;
            params.push_back({name, value});
        }
    }

    return params;
}

std::shared_ptr<Shader> Material::ParseMaterialShader(const std::string& filepath) {
    std::ifstream in(filepath);

    if (!in.is_open()) {
        std::cout << "Failed to open material: " << filepath << std::endl;
        return nullptr;
    }

    std::string shaderpath;

    std::string line;
    std::string prefix;
    while (getline(in, line)) {
        std::istringstream iss(line);
        iss >> prefix;

        if (prefix == "shader") {
            iss >> shaderpath;
            break;
        }
    }

    return std::make_shared<Shader>(shaderpath);
}