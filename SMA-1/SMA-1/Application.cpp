//
// Created by jonat on 08/04/2024.
//

#define GLM_ENABLE_EXPERIMENTAL

#include "Application.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.inl>

#include "Color.h"
#include "Camera/Camera.h"
#include "Window/Window.h"
#include "glad/glad.h"
#include "Input/Input.h"
#include "Mesh/Collision/Collision.h"
#include "Mesh/NPC/NPC.h"
#include "Shader/Shader.h"
#include "Shader/Buffers/Buffers.h"

//TODO : fix includes in window: shader, input and mouseinput
//TODO : fix init() in Camera

NPC npc;
Collision collision(glm::vec3(9, 0.5, -6), glm::vec3(2, 2, 1.f));
float timer = 0.f;

Camera Application::mCamera;

float Application::DeltaTime = 0.0f;


void Application::init() {
    mWindow = Window::init();
    mCamera.init();
    run();
}


void Application::create() {
    	// Player
	mMesh.CreateCube(glm::vec3(0, 0.5, 0.f), glm::vec3(0.75f, 1.3f, 0.75f),Color::Pink, false, true);
	mMesh.Package[0]->AddCollider(glm::vec3(0.75, 1.3, 1.2), ECollisionType::Player);

	// Pickups
	mMesh.CreateCube(glm::vec3(0.f, 1.f, -10.f), glm::vec3(1.f), Color::Gold, true);
	mMesh.Package.back()->AddCollider(glm::vec3(1.f),ECollisionType::Pickup);

	mMesh.CreateCube(glm::vec3(10.f, 1.f, -10.f), glm::vec3(1.f), Color::Gold, true);
	mMesh.Package.back()->AddCollider(glm::vec3(1.f),ECollisionType::Pickup);

	mMesh.CreateCube(glm::vec3(-5.f, 1.f, -4.f), glm::vec3(1.f), Color::Gold, true);
	mMesh.Package.back()->AddCollider(glm::vec3(1.f),ECollisionType::Pickup);

	mMesh.CreateCube(glm::vec3(5.f, 1.f, 0.f), glm::vec3(1.f), Color::Gold, true);
	mMesh.Package.back()->AddCollider(glm::vec3(1.f),ECollisionType::Pickup);

	mMesh.CreateCube(glm::vec3(30.f, 1.f, -10.f), glm::vec3(1.f), Color::Gold, true);
	mMesh.Package.back()->AddCollider(glm::vec3(1.f),ECollisionType::Pickup);

	mMesh.CreateCube(glm::vec3(25.f, 1.f, -10.f), glm::vec3(1.f), Color::Gold, true);
	mMesh.Package.back()->AddCollider(glm::vec3(1.f),ECollisionType::Pickup);

	mMesh.CreateCube(glm::vec3(-12.f, 1.f, -15.f), glm::vec3(1.f), Color::Gold, true);
	mMesh.Package.back()->AddCollider(glm::vec3(1.f),ECollisionType::Pickup);

	mMesh.CreateCube(glm::vec3(15.f, 1.f, -7.f), glm::vec3(1.f), Color::Gold, true);
	mMesh.Package.back()->AddCollider(glm::vec3(1.f),ECollisionType::Pickup);

	// Floor
	mMesh.CreateCube(glm::vec3(-20.f,0.f,20.f), glm::vec3(40.f,0.5,40.f), Color::Olive);
	mMesh.Package.back()->AddCollider(glm::vec3(40.f, 5.f, 40.f), ECollisionType::Wall);

	// NPC
	mMesh.CreateCube(glm::vec3(10.f, 10.f, -10.f), glm::vec3(1.f), Color::Pink);
	mMesh.Package.back()->AddCollider(glm::vec3(1.f),ECollisionType::NPC);

	// House - Walls
	mMesh.CreateCube(glm::vec3(15, 0.5, -5), glm::vec3(0.1, 2.5, 10), Color::Brown);
	mMesh.CreateCube(glm::vec3(5, 0.5, -15), glm::vec3(10, 2.5, 0.1), Color::Brown);
	mMesh.CreateCube(glm::vec3(5, 0.5, -5), glm::vec3(0.1, 2.5, 10), Color::Brown);

	// House - Roof
	mMesh.CreateCube(glm::vec3(5, 3, -5), glm::vec3(10.1, 0.1, 10), Color::Brown);

	// House - DoorFrame
	mMesh.CreateCube(glm::vec3(5, 0.5, -5), glm::vec3(4, 2.5, 0.1), Color::Brown);
	mMesh.CreateCube(glm::vec3(11, 0.5, -5), glm::vec3(4, 2.5, 0.1), Color::Brown);
	mMesh.CreateCube(glm::vec3(9, 2.5, -5), glm::vec3(2, 0.5, 0.1), Color::Brown);

	// Door
	mMesh.CreateCube(glm::vec3(9, 0.5, -5), glm::vec3(2, 2, 0.1), Color::Maroon, false, false,glm::vec3(0.f,1.f,0.f),true);
	mMesh.Package.back()->AddCollider(glm::vec3(2.f,2.f,0.5f), ECollisionType::Door,glm::vec3(0.f,0.f,0.5f));

	//Items in the house
	mMesh.CreateCube(glm::vec3(9,0.5,-10), glm::vec3(0.5,0.5,0.5), Color::Red);
	mMesh.Package.back()->bShouldRender = false;
	mMesh.CreateCube(glm::vec3(7,0.5,-8), glm::vec3(0.5,0.5,0.5), Color::Blue);
	mMesh.Package.back()->bShouldRender = false;
	mMesh.CreateCube(glm::vec3(11,0.5,-12), glm::vec3(0.5,0.5,0.5), Color::White);
	mMesh.Package.back()->bShouldRender = false;

	//NPC
	npc.initNPC();
}

void Application::update() {
	mMesh.Package[0]->Collider->checkCollision(*mMesh.Package[1]->Collider);
	mMesh.Package[0]->Collider->checkCollision(*mMesh.Package[2]->Collider);
	mMesh.Package[0]->Collider->checkCollision(*mMesh.Package[3]->Collider);
	mMesh.Package[0]->Collider->checkCollision(*mMesh.Package[4]->Collider);
	mMesh.Package[0]->Collider->checkCollision(*mMesh.Package[5]->Collider);
	mMesh.Package[0]->Collider->checkCollision(*mMesh.Package[6]->Collider);
	mMesh.Package[0]->Collider->checkCollision(*mMesh.Package[7]->Collider);
	mMesh.Package[0]->Collider->checkCollision(*mMesh.Package[8]->Collider);

	mMesh.Package[0]->Collider->checkCollision(*mMesh.Package[18]->Collider);

	if(collision.checkCollision(*mMesh.Package[0]->Collider))
	{
		for(int i = 19; i < 22; i++)
		{
			mMesh.Package[i]->bShouldRender = true;
		}
	}

	npc.updatePos(*mMesh.Package[10]);
	if(mMesh.Package[18]->bDoorInteracted)
	{
		mMesh.Package[18]->GetRotation().y -= 40.f * DeltaTime;
	}

}

void Application::run() {
	create();
	float FirstFrame = 0.0f;

	VertexArray VAO;
	VAO.Bind();

	VBO = new VertexBuffer(mMesh.mVertices);
	EBO = new ElementBuffer(mMesh.mIndices);

	VAO.Activate();
	glm::vec3 color(Color::Teal);
	while(!glfwWindowShouldClose(mWindow))
	{
		const auto CurrentFrame = static_cast<float>(glfwGetTime());
		DeltaTime = CurrentFrame - FirstFrame;
		FirstFrame = CurrentFrame;
		glClearColor(color.x, color.y, color.z, 1.f);
		glClear(GL_COLOR_BUFFER_BIT    | GL_DEPTH_BUFFER_BIT);
		glUseProgram(Shader::Program);
		KeyBoardInput::processInput(mWindow, mMesh.Package[0].get());
		update();
		glUniformMatrix4fv(mCamera.projectionLoc, 1, GL_FALSE, glm::value_ptr(mCamera.getProjection(Window::Width, Window::Height)));
		glUniformMatrix4fv(mCamera.viewLoc, 1, GL_FALSE, glm::value_ptr(mCamera.getView()));

		VAO.Bind();
		mMesh.Draw();
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
	glfwTerminate();

}





