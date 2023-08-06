#pragma once

#include <glad/glad.h>

#include <vector>
#include <array>

class StaticMesh
{
public:
    StaticMesh(float vertexData[], std::size_t n, uint32_t vertices);

    void SetVertexAttribute(int location, GLint size, GLenum type, GLsizei stride, const void* offset) const;

    void Draw() const;
    
    ~StaticMesh();

private:
    uint32_t VBO;
    uint32_t VAO;

    uint32_t m_vertices;
};
