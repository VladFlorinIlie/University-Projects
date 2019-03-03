#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <vector>
#include "LabCamera.h"
#include "Object.h"
#include "Table.h"
#include "TableHole.h"
#include "TableWall.h"
#include "Ball.h"
#include "Player.h"
#include "Stick.h"

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;
		Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 & color, bool shouldShine);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		CameraTema *camera;
		glm::mat4 projectionMatrix;
		std::vector<Object*> staticObjects;
		std::vector<Ball*> balls;
		std::vector<Player*> players;
		Ball* mainBall;
		Stick* stick;
		bool debug;
		bool ballsAlreadyStopped;
		float impulse;
		bool thirdPerson;
		int currentPlayer;
		bool fault;
		bool ballHasEntered;
		bool canMoveBall;
		bool firstTouch;
		bool gameStart;
		int nrOfBalls;
		bool mouseBtnPressed;
		bool end;

		glm::vec3 lightPosition;
		glm::vec3 lightPosition2;
		glm::vec3 lightPosition3;
		glm::vec3 lightDirection;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;
};
