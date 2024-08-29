#include "Buffers.h"
#include "../../Mesh/Mesh.h"
#include "glad/glad.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &va);
    Bind();
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &va);
}

void VertexArray::Bind() const
{
    glBindVertexArray(va);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::Activate() const
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glBindVertexArray(1);
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& objectVector)
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, objectVector.size() * sizeof(Vertex), objectVector.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &vbo);
}

void VertexBuffer::Bind(const std::vector<Vertex>& objectVector) const
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, objectVector.size() * sizeof(Vertex), objectVector.data(), GL_STATIC_DRAW);
}

ElementBuffer::ElementBuffer(const std::vector<unsigned>& objectVector)
{
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, objectVector.size() * sizeof(unsigned int), objectVector.data(), GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &ebo);
}

void ElementBuffer::Bind(const std::vector<unsigned>& objectVector) const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, objectVector.size() * sizeof(unsigned int), objectVector.data(), GL_STATIC_DRAW);
}
