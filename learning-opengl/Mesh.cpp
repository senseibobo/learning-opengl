#include "Mesh.h"

Mesh::Mesh(float* vertices, uint32_t* indices, int vertexCount, int indexCount)
{
    SetVertices(vertices, indices, vertexCount, indexCount);
}

GLsizei Mesh::GetVertexCount() const
{
    return vertexCount;
}

GLsizei Mesh::GetIndexCount() const
{
    return indexCount;
}

GLuint Mesh::GetVAO() const
{
    return VAO;
}

void Mesh::SetVAO(GLuint VAO)
{
    this->VAO = VAO;
}

void Mesh::SetVertices(float* vertices, uint32_t* indices, int vertexCount, int indexCount)
{

    GLsizei stride = 14 * sizeof(float);
    this->vertexCount = vertexCount;
    this->indexCount = indexCount;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*stride, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6*sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(8*sizeof(float)));
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (void*)(11*sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);

}