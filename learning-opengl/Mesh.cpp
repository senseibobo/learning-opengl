#include "Mesh.h"

Mesh::Mesh(float* vertices, int vertexCount)
{
    SetVertices(vertices, vertexCount);
}

GLsizei Mesh::GetVertexCount() const
{
    return vertexCount;
}

GLuint Mesh::GetVAO() const
{
    return VAO;
}

void Mesh::SetVAO(GLuint VAO)
{
    this->VAO = VAO;
}

void Mesh::SetVertices(float* vertices, int count)
{

    GLsizei stride = 8 * sizeof(float);
    vertexCount = count;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, count*stride, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(5*sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}