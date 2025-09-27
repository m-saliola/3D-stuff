#include "material.h"

Material::Material(const std::string& filepath) : m_Shader(ParseMaterialShader(filepath)), m_Params(ParseMaterial(filepath)) { 
    Bind();
    SetUniforms();
}

void Material::Bind() const { 
    m_Shader.Bind();
}

void Material::Unbind() const { 
    m_Shader.Unbind();
}

void Material::SetUniforms() const {
    for (const auto& param : m_Params) {
        std::visit([&](auto&& value) {
            using T = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<T, int>) {
                m_Shader.SetUniform<1, int>(param.name, value);
            } else if constexpr (std::is_same_v<T, unsigned int>) {
                m_Shader.SetUniform<1, unsigned int>(param.name, value);
            } else if constexpr (std::is_same_v<T, float>) {
                m_Shader.SetUniform<1, float>(param.name, value);
            } else if constexpr (std::is_same_v<T, glm::vec2>) {
                m_Shader.SetUniform<2, float>(param.name, value.x, value.y);
            } else if constexpr (std::is_same_v<T, glm::vec3>) {
                m_Shader.SetUniform<3, float>(param.name, value.x, value.y, value.z);
            } else if constexpr (std::is_same_v<T, glm::vec4>) {
                m_Shader.SetUniform<4, float>(param.name, value.x, value.y, value.z, value.w);
            } else if constexpr (std::is_same_v<T, glm::mat2>) {
                m_Shader.SetUniform<1, glm::mat2>(param.name, value);
            } else if constexpr (std::is_same_v<T, glm::mat3>) {
                m_Shader.SetUniform<1, glm::mat3>(param.name, value);
            } else if constexpr (std::is_same_v<T, glm::mat4>) {
                m_Shader.SetUniform<1, glm::mat4>(param.name, value);
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

    std::string line;
    std::vector<MaterialParameter> params;

    while (getline(in, line)) {
        if (line.find("<int>") != std::string::npos) {
            int start = line.find('>');
            int end = line.find('=');
            int len = end - start - 1;

            std::string name = line.substr(start + 1, len);
            int value = stoi(line.substr(end + 1));

            params.push_back({name, value});
        } else if (line.find("<float>") != std::string::npos) {
            int start = line.find('>');
            int end = line.find('=');
            int len = end - start - 1;

            std::string name = line.substr(start + 1, len);
            float value = stof(line.substr(end + 1));

            params.push_back({name, value});
        } else if (line.find("<vec2>") != std::string::npos) {
            int start = line.find('>');
            int end = line.find('=');
            int len = end - start - 1;

            std::string name = line.substr(start + 1, len);
            std::stringstream ss(line.substr(end + 1));

            glm::vec2 value;
            std::string token;

            std::getline(ss, token, ','); value.x = stof(token);
            std::getline(ss, token, ','); value.y = stof(token);

            params.push_back({name, value});
        } else if (line.find("<vec3>") != std::string::npos) {
            int start = line.find('>');
            int end = line.find('=');
            int len = end - start - 1;

            std::string name = line.substr(start + 1, len);
            std::stringstream ss(line.substr(end + 1));

            glm::vec3 value;
            std::string token;

            std::getline(ss, token, ','); value.x = stof(token);
            std::getline(ss, token, ','); value.y = stof(token);
            std::getline(ss, token, ','); value.z = stof(token);

            params.push_back({name, value});
        } else if (line.find("<vec4>") != std::string::npos) {
            int start = line.find('>');
            int end = line.find('=');
            int len = end - start - 1;

            std::string name = line.substr(start + 1, len);
            std::stringstream ss(line.substr(end + 1));

            glm::vec4 value;
            std::string token;

            std::getline(ss, token, ','); value.x = stof(token);
            std::getline(ss, token, ','); value.y = stof(token);
            std::getline(ss, token, ','); value.z = stof(token);
            std::getline(ss, token, ','); value.w = stof(token);

            params.push_back({name, value});
        }
    }

    return params;
}

Shader Material::ParseMaterialShader(const std::string& filepath) {
    std::ifstream in(filepath);

    if (!in.is_open()) {
        std::cout << "Failed to open material: " << filepath << std::endl;
        return Shader("");
    }

    std::string line;
    std::string shaderpath;

    while (getline(in, line)) {
        if (line.find("shader=") != std::string::npos) {
            int start = line.find('=');
            shaderpath = line.substr(start + 1);
        }
    }

    return Shader(shaderpath);
}