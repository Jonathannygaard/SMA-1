#pragma once
#include <memory>
#include "Collision/Collision.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Pickup;

struct Vertex
{
    float x, y, z;
    glm::vec3 Color;
    Vertex(float x, float y, float z, glm::vec3 rgb) : x(x), y(y), z(z), Color(rgb)
    {
    }
};

class Cube;

class Mesh
{
    int count = 0;

public:
    std::vector<Vertex> mVertices;
    std::vector<GLuint> mIndices;
    std::vector<std::shared_ptr<Cube>> Package;

    void Draw();
    void CreateCube(glm::vec3 position, glm::vec3 scale, glm::vec3 color, bool isPickup = false, bool isPlayer = false, glm::vec3 rotation = glm::vec3(0.f), bool isDoor = false);
};

class Cube{
    int index = 0;
    glm::vec3 Position;
    glm::vec3 Scale;
    glm::vec3 Rotation;

public:
    Cube(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
        : Position(position), Scale(scale), Rotation(rotation)
    {}
    bool bIsPlayer = false;
    bool bCanInteract = false;
    bool bIsPickup = false;
    bool bShouldRender = true;
    bool bIsDoor = false;
    bool bDoorInteracted = false;

    Cube* OverlappedCube = nullptr;

    std::shared_ptr<Collision> Collider;
    glm::vec3& GetPosition() { return Position; }
    glm::vec3& GetScale() { return Scale; }
    glm::vec3& GetRotation() { return Rotation; }
    int& GetIndex() { return index; }
    void AddCollider(glm::vec3 scale,ECollisionType collisionType, glm::vec3 offset = glm::vec3(0.f));
    virtual ~Cube();
};


