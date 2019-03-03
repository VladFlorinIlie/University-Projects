#pragma once

#include "Object.h"

class Ball : public Object {

private:
	int ballType; // 0 = alba; 1 = neagra; 2 = rosie; 3 = galbena
	glm::vec3 velocity = glm::vec3(0);
	float oldDeltaTime = 1;
	float mass = 0.16f;
	float gravAcc = 9.8f;
	float frictionCt = 0.16f;
	float lastDist = 0;

	void velocityAfterFriction();

public:
	Ball();
	~Ball();

	void reset();
	void touch();
	void update(float deltaTime);
	void setBallType(int type);
	int getBallType();
	void setVelocity(glm::vec3 velocity);
	glm::vec3 getVelocity();

	void setLocation(float x, float y, float z);

	int checkCollisionHole(Object* hole);
	void checkCollisionWall(Object* wall);
	bool checkCollisionBall(Ball* other);
	void bounce(Ball* other);

};