#define GLM_ENABLE_EXPERIMENTAL

#include "Mesh.h"
#include "../Shader/Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

void Mesh::	CreateCube(glm::vec3 position, glm::vec3 scale, glm::vec3 color, bool isPickup, bool isPlayer, glm::vec3 rotation, bool isDoor)
{

	Package.emplace_back(std::make_shared<Cube>(position, scale, rotation));
	Package.back()->GetIndex() = static_cast<int>(Package.size() - 1);
	Package.back()->bIsPlayer = isPlayer;
	Package.back()->bIsPickup = isPickup;
	Package.back()->bIsDoor = isDoor;

	Vertex v0{0.f, 0.f, 0.f, color}; /* Front-Bot-left */
	Vertex v1{1.f, 0.f, 0.f, color}; /* Front-Bot-right */
	Vertex v2{1.f, 1.f, 0.f, color}; /* Front-Top-right */
	Vertex v3{0.f, 1.f, 0.f, color}; /* Front-Top-left */
	Vertex v4{0.f, 0.f, -1.f, color}; /* Back-Bot-left */
	Vertex v5{1.f, 0.f, -1.f, color}; /* Back-Bot-right */
	Vertex v6{1.f, 1.f, -1.f, color}; /* Back-Top-right */
	Vertex v7{0.f, 1.f, -1.f, color}; /* Back-Top-left */

	mVertices.emplace_back(v0);
	mVertices.emplace_back(v1);
	mVertices.emplace_back(v2);
	mVertices.emplace_back(v3);
	mVertices.emplace_back(v4);
	mVertices.emplace_back(v5);
	mVertices.emplace_back(v6);
	mVertices.emplace_back(v7);

	/* Front */
	mIndices.emplace_back(0 + count);
	mIndices.emplace_back(1 + count);
	mIndices.emplace_back(2 + count);
	mIndices.emplace_back(2 + count);
	mIndices.emplace_back(3 + count);
	mIndices.emplace_back(0 + count);

	/* Right */
	mIndices.emplace_back(1 + count);
	mIndices.emplace_back(5 + count);
	mIndices.emplace_back(6 + count);
	mIndices.emplace_back(6 + count);
	mIndices.emplace_back(2 + count);
	mIndices.emplace_back(1 + count);

	/* Left */
	mIndices.emplace_back(0 + count);
	mIndices.emplace_back(3 + count);
	mIndices.emplace_back(7 + count);
	mIndices.emplace_back(7 + count);
	mIndices.emplace_back(4 + count);
	mIndices.emplace_back(0 + count);

	/* Back */
	mIndices.emplace_back(4 + count);
	mIndices.emplace_back(7 + count);
	mIndices.emplace_back(6 + count);
	mIndices.emplace_back(6 + count);
	mIndices.emplace_back(5 + count);
	mIndices.emplace_back(4 + count);

	/* Top */
	mIndices.emplace_back(3 + count);
	mIndices.emplace_back(2 + count);
	mIndices.emplace_back(6 + count);
	mIndices.emplace_back(6 + count);
	mIndices.emplace_back(7 + count);
	mIndices.emplace_back(3 + count);

	/* Bottom */
	mIndices.emplace_back(0 + count);
	mIndices.emplace_back(4 + count);
	mIndices.emplace_back(5 + count);
	mIndices.emplace_back(5 + count);
	mIndices.emplace_back(1 + count);
	mIndices.emplace_back(0 + count);

	count += 8;

}

void Cube::AddCollider(glm::vec3 scale, ECollisionType collisionType, glm::vec3 offset)
{
	Collider = std::make_unique<Collision>(GetPosition()+offset,scale, offset,collisionType,this);
}

Cube::~Cube()
{
}

void Mesh::Draw()
{
	for (auto& cube:Package)
	{
		if(cube->bShouldRender)
		{
			if (cube->Collider)
				cube->Collider->UpdatePosition(cube->GetPosition()+cube->Collider->offset);
			glm::mat4 model(1.f);
			model = glm::translate(model, cube->GetPosition());
			if(cube->bDoorInteracted)
			{
				if(cube->GetRotation().y < -90.f)
					cube->GetRotation().y = -90.f;
				model = glm::rotate(model, glm::radians(cube->GetRotation().x), glm::vec3(1.f, 0.f, 0.f));
				model = glm::rotate(model, glm::radians(cube->GetRotation().y), glm::vec3(0.f, 1.f, 0.f));
				model = glm::rotate(model, glm::radians(cube->GetRotation().z), glm::vec3(0.f, 0.f, 1.f));
			}
			model = glm::scale(model, cube->GetScale());
			glUniformMatrix4fv(glGetUniformLocation(Shader::Program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(cube->GetIndex() * 36 * sizeof(unsigned int)));
		}
	}
}
