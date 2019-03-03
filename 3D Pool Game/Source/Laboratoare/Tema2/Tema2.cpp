#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	camera = new CameraTema();
	camera->Set(glm::vec3(0, 7, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1));

	debug = false;
	thirdPerson = false;
	currentPlayer = 0;
	ballsAlreadyStopped = true;
	fault = false;
	ballHasEntered = false;
	canMoveBall = true;
	firstTouch = true;
	gameStart = true;
	nrOfBalls = 15;
	end = false;
	mouseBtnPressed = false;

	{
		lightPosition = glm::vec3(0, 5, -2.5f);
		lightPosition2 = glm::vec3(0, 5, 0);
		lightPosition3 = glm::vec3(0, 5, 2.5f);
		lightDirection = glm::vec3(0, -1, 0);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
	}

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	{
		Shader *shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("ColorShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/ColorVertex.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	std::cout << "Player " << currentPlayer << " starts!" << std::endl;

	Player *player = new Player(0);
	players.push_back(player);

	player = new Player(0);
	players.push_back(player);

	stick = new Stick();
	stick->init(meshes["box"], glm::vec3(0, 2.0f, 0), glm::vec3(0.05f, 0.05f, 2.0f), glm::vec3(0.5, 0, 0));

	{
		Object* table = new Table();
		table->init(meshes["box"], glm::vec3(0, 0.5f, 0), glm::vec3(3.0f, 1.0f, 6.0f), glm::vec3(0, 1, 0));
		staticObjects.push_back(table);

		Object* leftWall = new TableWall();
		leftWall->init(meshes["box"], glm::vec3(-1.4f, 1.1f, 0), glm::vec3(0.2f, 0.2f, 6.0f), glm::vec3(0, 0.5f, 0));
		staticObjects.push_back(leftWall);

		Object* rightWall = new TableWall();
		rightWall->init(meshes["box"], glm::vec3(1.4f, 1.1f, 0), glm::vec3(0.2f, 0.2f, 6.0f), glm::vec3(0, 0.5f, 0));
		staticObjects.push_back(rightWall);

		Object* downWall = new TableWall();
		downWall->init(meshes["box"], glm::vec3(0, 1.1f, 2.9f), glm::vec3(3.0f, 0.2f, 0.2f), glm::vec3(0, 0.5f, 0));
		staticObjects.push_back(downWall);

		Object* upWall = new TableWall();
		upWall->init(meshes["box"], glm::vec3(0, 1.1f, -2.9f), glm::vec3(3.0f, 0.2f, 0.2f), glm::vec3(0, 0.5f, 0));
		staticObjects.push_back(upWall);

		Object* leftDownHole = new TableHole();
		leftDownHole->init(meshes["sphere"], glm::vec3(-1.27f, 1.0f, 2.77f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0, 0, 0));
		staticObjects.push_back(leftDownHole);

		Object* rightDownHole = new TableHole();
		rightDownHole->init(meshes["sphere"], glm::vec3(1.27f, 1.0f, 2.77f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0, 0, 0));
		staticObjects.push_back(rightDownHole);

		Object* rightHole = new TableHole();
		rightHole->init(meshes["sphere"], glm::vec3(1.35f, 1.0f, 0), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0, 0, 0));
		staticObjects.push_back(rightHole);

		Object* leftHole = new TableHole();
		leftHole->init(meshes["sphere"], glm::vec3(-1.35f, 1.0f, 0), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0, 0, 0));
		staticObjects.push_back(leftHole);

		Object* leftUpHole = new TableHole();
		leftUpHole->init(meshes["sphere"], glm::vec3(-1.27f, 1.0f, -2.77f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0, 0, 0));
		staticObjects.push_back(leftUpHole);

		Object* rightUpHole = new TableHole();
		rightUpHole->init(meshes["sphere"], glm::vec3(1.27f, 1.0f, -2.77f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0, 0, 0));
		staticObjects.push_back(rightUpHole);

		//main ball
		mainBall = new Ball();
		mainBall->init(meshes["sphere"], glm::vec3(0, 1.1f, 2.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 1, 1));
		mainBall->setBallType(0);
		balls.push_back(mainBall);

		//first row
		Ball *ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(0, 1.1f, -2.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 1, 0));
		ball->setBallType(3);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(-0.21f, 1.1f, -2.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 1, 0));
		ball->setBallType(3);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(0.21f, 1.1f, -2.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 0, 0));
		ball->setBallType(2);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(-0.42f, 1.1f, -2.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 0, 0));
		ball->setBallType(2);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(0.42f, 1.1f, -2.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 0, 0));
		ball->setBallType(2);
		balls.push_back(ball);

		//second row
		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(-0.105, 1.1f, -2.09f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 0, 0));
		ball->setBallType(2);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(0.105, 1.1f, -2.09f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 0, 0));
		ball->setBallType(2);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(-0.315, 1.1f, -2.09f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 1, 0));
		ball->setBallType(3);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(0.315, 1.1f, -2.09f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 1, 0));
		ball->setBallType(3);
		balls.push_back(ball);

		//third row
		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(0, 1.1f, -1.88f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.1f, 0.1f, 0.1f));
		ball->setBallType(1);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(-0.21f, 1.1f, -1.88f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 0, 0));
		ball->setBallType(2);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(0.21f, 1.1f, -1.88f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 1, 0));
		ball->setBallType(3);
		balls.push_back(ball);

		//fourth row
		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(-0.105, 1.1f, -1.67f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 1, 0));
		ball->setBallType(3);
		balls.push_back(ball);

		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(0.105, 1.1f, -1.67f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 0, 0));
		ball->setBallType(2);
		balls.push_back(ball);

		//fifth row
		ball = new Ball();
		ball->init(meshes["sphere"], glm::vec3(0, 1.1f, -1.46f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 0, 0));
		ball->setBallType(2);
		balls.push_back(ball);
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	if (thirdPerson) {
		if (mouseBtnPressed) {
			impulse += 0.1f * deltaTimeSeconds;
			if (impulse > 0.1f) {
				impulse = 0;
			}
		}
		if (currentPlayer == 0) {
			RenderMesh(stick->getMesh(), shaders["ShaderTema2"], stick->getRotatedMat(), glm::vec3(0, 1, 1), true);
		}
		else {
			RenderMesh(stick->getMesh(), shaders["ShaderTema2"], stick->getRotatedMat(), glm::vec3(0, 0, 1), true);
		}
	}

	bool ballsStopped = true;
	if (!canMoveBall) {
		for (int i = 0; i < balls.size(); i++) {
			if (balls[i]->getIsDestroyed()) {
				continue;
			}

			for (Object* obj : staticObjects) {
				TableWall *wall = dynamic_cast<TableWall*>(obj);
				if (wall != NULL) {
					balls[i]->checkCollisionWall(obj);
				}

				TableHole *hole = dynamic_cast<TableHole*>(obj);
				if (hole != NULL) {
					int type = balls[i]->checkCollisionHole(obj);
					if (type != -1) {
						std::cout << "A ball of type: " << type << " has entered the pocket." << std::endl;
						if (type == 0) {
							std::cout << "Fault: White ball has entered the pocket." << std::endl;
							fault = true;
						}
						else if (type == 1) {
							if (nrOfBalls == 1) {
								std::cout << "Player " << currentPlayer << " has won!" << std::endl;
							}
							else {
								std::cout << "Player " << (currentPlayer + 1) % 2 << " has won!" << std::endl;
							}
							end = true;
						}
						else if (players[currentPlayer]->getBallType() == -1) {
							players[currentPlayer]->setBallType(type);
							players[currentPlayer]->setNoOfBalls(1);

							players[(currentPlayer + 1) % 2]->setBallType(type == 3 ? 2 : 3);

							std::cout << "Player " << currentPlayer << " has type of balls: " << type << std::endl;
							std::cout << "Player " << (currentPlayer + 1) % 2 << " has type of balls: " << (type == 3 ? 2 : 3) << std::endl;

							ballHasEntered = true;
						}
						else if (players[currentPlayer]->getBallType() == type) {
							players[currentPlayer]->setNoOfBalls(players[currentPlayer]->getNoOfBalls() + 1);

							std::cout << "Player " << currentPlayer << " has score: " << players[currentPlayer]->getNoOfBalls() << std::endl;

							ballHasEntered = true;
						}
						else {
							players[(currentPlayer + 1) % 2]->setNoOfBalls(players[(currentPlayer + 1) % 2]->getNoOfBalls() + 1);
							std::cout << "Fault: Pocketed wrong ball." << std::endl;
							fault = true;
						}
					}
				}
			}

			for (int j = i + 1; j < balls.size(); j++) {
				if (balls[j]->getIsDestroyed()) {
					continue;
				}

				if (balls[i]->checkCollisionBall(balls[j])) {
					balls[i]->bounce(balls[j]);

					if (i == 0 && firstTouch) {
						firstTouch = false;
						if (players[currentPlayer]->getBallType() != -1 && players[currentPlayer]->getBallType() != balls[j]->getBallType()) {
							std::cout << "Fault: Touched wrong ball." << std::endl;
							fault = true;
						}
					}
				}
			}
		}
	}

	for (Object* obj : staticObjects) {
		obj->update(deltaTimeSeconds);
		RenderMesh(obj->getMesh(), shaders["ColorShader"], obj->getModelMatrix(), obj->getColor(), false);
	}

	for (int i = 0; i < balls.size(); i++) {
		if (balls[i]->getIsDestroyed()) {
			continue;
		}

		balls[i]->update(deltaTimeSeconds);
		RenderMesh(balls[i]->getMesh(), shaders["ColorShader"], balls[i]->getModelMatrix(), balls[i]->getColor(), true);

		if (glm::length2(balls[i]->getVelocity()) != 0) {
			ballsStopped = false;
		}
	}

	if (ballsStopped && !ballsAlreadyStopped && !end) {
		ballsAlreadyStopped = true;
		std::cout << "------------ SCORE ------------" << std::endl;
		std::cout << "Player 0: " << players[0]->getNoOfBalls() << std::endl;
		std::cout << "Player 1: " << players[1]->getNoOfBalls() << std::endl;
		std::cout << "------------ SCORE ------------" << std::endl;
		if (!ballHasEntered || fault) {
			currentPlayer = (currentPlayer + 1) % 2;
			std::cout << "Player " << currentPlayer << " will play now!" << std::endl;
			if (fault) {
				fault = false;
				canMoveBall = true;
				mainBall->setLocation(-mainBall->getCenter().x, 0, -mainBall->getCenter().z + 2.3f);
				mainBall->setIsDestroyed(false);
			}
		}
		ballHasEntered = false;
		firstTouch = true;
	}
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

void Tema2::RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 & color, bool shouldShine)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	int location;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// get shader location for uniform mat4 "Model"
	location = glGetUniformLocation(shader->program, "Model");

	// set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// get shader location for uniform mat4 "View"
	location = glGetUniformLocation(shader->program, "View");

	// set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// get shader location for uniform mat4 "Projection"
	location = glGetUniformLocation(shader->program, "Projection");

	// set shader uniform "Projection" to projectionMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->program, "color");
	glUniform3fv(location, 1, glm::value_ptr(color));

	location = glGetUniformLocation(shader->program, "impulse");
	glUniform1f(location, impulse);

	location = glGetUniformLocation(shader->program, "direction"); // if working in world space
	glUniform3fv(location, 1, glm::value_ptr(glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z))));

	location = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(location, 1, glm::value_ptr(lightPosition));

	location = glGetUniformLocation(shader->program, "light_position2");
	glUniform3fv(location, 1, glm::value_ptr(lightPosition2));

	location = glGetUniformLocation(shader->program, "light_position3");
	glUniform3fv(location, 1, glm::value_ptr(lightPosition3));

	location = glGetUniformLocation(shader->program, "light_direction");
	glUniform3fv(location, 1, glm::value_ptr(lightDirection));

	// Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->position;
	location = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(location, 1, glm::value_ptr(eyePosition));

	// Set material property uniforms (shininess, kd, ks, object color) 
	location = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(location, materialKd);
	location = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(location, materialKs);

	location = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(location, materialShininess);
	location = glGetUniformLocation(shader->program, "should_shine");
	glUniform1i(location, shouldShine ? 1 : 0);

	location = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(location, 1, glm::value_ptr(color));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && debug)
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->MoveForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->MoveForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->MoveUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->MoveUpword(deltaTime * cameraSpeed);
		}
	}
	else if (canMoveBall && !end && !debug) {
		float moveSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			if (!gameStart && mainBall->getCenter().z - moveSpeed * deltaTime - mainBall->getScale().x / 2 >= -2.8f) {
				mainBall->setLocation(0, 0, -moveSpeed * deltaTime);
			}
			else if (mainBall->getCenter().z - moveSpeed * deltaTime - mainBall->getScale().x / 2 >= 1.0f) {
				mainBall->setLocation(0, 0, -moveSpeed * deltaTime);
			}
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			if (mainBall->getCenter().x - moveSpeed * deltaTime - mainBall->getScale().x / 2 >= -1.3f) {
				mainBall->setLocation(-moveSpeed * deltaTime, 0, 0);
			}
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			if (mainBall->getCenter().z + moveSpeed * deltaTime + mainBall->getScale().x / 2 <= 2.8f) {
				mainBall->setLocation(0, 0, moveSpeed * deltaTime);
			}
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			if (mainBall->getCenter().x + moveSpeed * deltaTime + mainBall->getScale().x / 2 <= 1.3f) {
				mainBall->setLocation(moveSpeed * deltaTime, 0, 0);
			}
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE && ballsAlreadyStopped && !end) {
		camera->Set(glm::vec3(mainBall->getCenter().x, mainBall->getCenter().y + 1.0f, mainBall->getCenter().z + 2.0f),
			mainBall->getCenter(), glm::vec3(0, 1, 0));
		stick->setCenter(glm::vec3(mainBall->getCenter().x, mainBall->getCenter().y + 0.1f, mainBall->getCenter().z + 1.3f));
		thirdPerson = true;
		canMoveBall = false;
		gameStart = false;
	}
	else if (key == GLFW_KEY_U) {
		debug = !debug;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	float sensivityOX = 0.001f;
	float sensivityOY = 0.001f;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (!thirdPerson && debug) {
			// rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
		}

		if (thirdPerson && !debug) {
			stick->spinAround(mainBall->getCenter(), -deltaX * sensivityOY);
			camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
		}
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && thirdPerson) {
		impulse = 0;
		mouseBtnPressed = true;
	}
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && thirdPerson) {
		mouseBtnPressed = false;
		glm::vec3 cameraForward = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));
		mainBall->setVelocity(cameraForward * impulse);

		camera->Set(glm::vec3(0, 7, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1));
		thirdPerson = false;
		ballsAlreadyStopped = false;
		impulse = 0;
	}
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
