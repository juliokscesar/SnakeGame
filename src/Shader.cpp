#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

std::string readFromFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "ERROR::IO::FILE_NOT_FOUND\n\"" << path << "\"\n";
        return "";
    }

    // Ensure file handler can throw exceptions
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string fileContent{};
    try
    {
        std::stringstream contentStrStream;
        // Read file buffer into stream
        contentStrStream << file.rdbuf();

        // Close file
        file.close();

        fileContent = contentStrStream.str();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return "";
    }
    
    return fileContent;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexStr = readFromFile(vertexPath);
    std::string fragmentStr = readFromFile(fragmentPath);

    const char* vertexCode   = vertexStr.c_str();
    const char* fragmentCode = fragmentStr.c_str(); 


    /// Compile shaders
    uint32_t vertexId, fragmentId;
    int success;
    char infoLog[512];

    // Vertex Shader
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertexCode, nullptr);
    glCompileShader(vertexId);
    // Check for compiling errors
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexId, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILE::VERTEX\n\t" << infoLog << "\n";
    }

    // Fragment Shader
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragmentCode, nullptr);
    glCompileShader(fragmentId);
    // Check for compiling errors
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentId, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILE::FRAGMENT\n\t" << infoLog << "\n";
    }

    // Shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexId);
    glAttachShader(ID, fragmentId);
    glLinkProgram(ID);
    // Check for errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::LINK::PROGRAM\n\t" << infoLog << "\n";
    }

    // Delete the shaders as they're linked to our program and are no longer necessary
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

void Shader::Use() const
{
    glUseProgram(ID);
}

uint32_t Shader::GetUniformLocation(const std::string& name) const
{
    return glGetUniformLocation(ID, name.c_str());
}

void Shader::SetUniformInt(const std::string& name, int value) const
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformFloat(const std::string& name, float value) const
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformBool(const std::string& name, bool value) const
{
    glUniform1i(GetUniformLocation(name), static_cast<int>(value));
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));   
}
