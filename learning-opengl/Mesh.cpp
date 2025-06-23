#include "Mesh.h"

Mesh::Mesh(float* vertices, int vertexCount, Shader* shader, Camera* camera)
{
    this->shader = shader;
    this->camera = camera;
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    SetVertices(vertices, vertexCount);
}

glm::mat4 Mesh::GetModelMatrix() const
{
    return modelMatrix;
}

void Mesh::SetPosition(const glm::vec3& position)
{
    this->position = position;
    updateModelMatrix();
}

void Mesh::SetRotation(const glm::vec3& rotation)
{
    this->rotation = rotation;
    updateModelMatrix();
}

void Mesh::SetScale(const glm::vec3& scale)
{
    this->scale = scale;
    updateModelMatrix();
}

glm::vec3 Mesh::GetPosition() const
{
    return position;
}

glm::vec3 Mesh::GetRotation() const
{
    return rotation;
}

glm::vec3 Mesh::GetScale() const
{
    return scale;
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

    GLsizei stride = 5 * sizeof(float);
    vertexCount = count;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, count*stride, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

Shader* Mesh::GetShader()
{
    return shader;
}

void Mesh::SetShader(Shader* shader)
{
    this->shader = shader;
}

void Mesh::SetCamera(Camera* camera)
{
    this->camera = camera;
}

void Mesh::Draw() const
{
    shader->Use();
    shader->SetMat4("model", GetModelMatrix());
    shader->SetMat4("projection", camera->GetProjectionMatrix());
    shader->SetMat4("view", camera->GetViewMatrix());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    std::cout << "drawingg\n";
}

void Mesh::updateModelMatrix()
{
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, GetPosition());
    modelMatrix = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
    modelMatrix = glm::scale(modelMatrix, scale);
}
