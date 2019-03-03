#pragma once

#include "Object.h"

class Stick : public Object {

private:
	glm::mat4 rotatedMat = glm::mat4(1);

public:
	Stick();
	~Stick();

	void reset();
	void touch();
	void update(float deltaTime);

	void setCenter(glm::vec3 center);
	void spinAround(glm::vec3 ballPos, float degree);
	glm::mat4 getRotatedMat();

};