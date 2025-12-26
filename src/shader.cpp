#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "renderer.h"

Shader::Shader(const std::string& filepath) {
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
    if (m_RendererID) glDeleteProgram(m_RendererID);
}

int Shader::GetUniformLocation(const std::string &name) const {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::Bind() const {
    glUseProgram(m_RendererID);
}
void Shader::Unbind() const {
    glUseProgram(0);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::ifstream in(filepath);

    if (!in.is_open()) {
        std::cout << "Failed to open shader: " << filepath << std::endl;
        return {};
    }

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while (getline(in, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else ss[(int)type] << line << '\n';
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len); 
        char* message = (char*)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);
        std::cout << "Failed to compile shader! " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
