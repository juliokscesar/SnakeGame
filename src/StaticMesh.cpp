#include "StaticMesh.h"

#include <iostream>

StaticMesh::StaticMesh(float vertexData[], std::size_t n, uint32_t vertices)
{
    m_vertices = vertices;

    // Generate VAO and VBO first
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, n, vertexData, GL_STATIC_DRAW);
}

void StaticMesh::SetVertexAttribute(int location, GLint size, GLenum type, GLsizei stride, const void* offset) const
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(location, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(location);
}

void StaticMesh::Draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices);
}

StaticMesh::~StaticMesh()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}
