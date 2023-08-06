#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Shader
{
public:
    uint32_t ID;

    // Constructor takes vertex and fragment shaders path and compiles it
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void Use() const;

    uint32_t GetUniformLocation(const std::string& name) const;

    // Uniform Setters
    void SetUniformInt(const std::string& name, int value) const;
    void SetUniformFloat(const std::string& name, float value) const;
    void SetUniformBool(const std::string& name, bool value) const;
    void SetUniformMat4(const std::string& name, const glm::mat4& value) const;
};