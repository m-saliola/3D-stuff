#pragma once

#include <glad/glad.h>
#include <unordered_map>
// #include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

// struct Uniform {
//     std::string name;
//     unsigned int type;
//     int size;
//     int location;
// };

class Shader {
private:
    unsigned int m_RendererID;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;

    int GetUniformLocation(const std::string& name) const;
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
 
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    template <int N, typename T, typename... Args>
    void SetUniform(const std::string& name, Args&&... args) const {
        int location = GetUniformLocation(name);

        if constexpr (std::is_same_v<T, float>) {
            if constexpr (N == 1) glUniform1f(location, args...);
            else if constexpr (N == 2) glUniform2f(location, args...);
            else if constexpr (N == 3) glUniform3f(location, args...);
            else if constexpr (N == 4) glUniform4f(location, args...);
        } else if constexpr (std::is_same_v<T, int>) {
            if constexpr (N == 1) glUniform1i(location, args...);
            else if constexpr (N == 2) glUniform2i(location, args...);
            else if constexpr (N == 3) glUniform3i(location, args...);
            else if constexpr (N == 4) glUniform4i(location, args...);
        } else if constexpr (std::is_same_v<T, glm::mat2>) {
            glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(std::forward<Args>(args)...));
        } else if constexpr (std::is_same_v<T, glm::mat3>) {
            glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(std::forward<Args>(args)...));
        } else if constexpr (std::is_same_v<T, glm::mat4>) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(std::forward<Args>(args)...));
        }
    }

    // std::vector<Uniform> GetUniforms() const {
    //     int count, bufSize, length, size;
    //     unsigned int type;
    //     glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORMS, &count);
    //     glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufSize);
    //     char* buffer = (char*)malloc(bufSize);

    //     std::vector<Uniform> uniforms;

    //     for (int i = 0; i < count; i++) {
    //         glGetActiveUniform(m_RendererID, i, bufSize, &length, &size, &type, buffer);
    //         uniforms.push_back({std::string(buffer), type, size, GetUniformLocation(buffer)});
    //         std::cout << buffer << ' ' << length << ' ' << size << ' ' << GetUniformLocation(buffer) << std::endl;
    //     }

    //     free(buffer);

    //     return uniforms;
    // }
};