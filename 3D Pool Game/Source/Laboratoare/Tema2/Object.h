#pragma once

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <iostream>
#include <cmath>
#include <algorithm>

class Object {

protected:
	Mesh* mesh;
	glm::mat4 modelMatrix;
	glm::vec3 color;
	glm::vec3 center;
	glm::vec3 scale;
	bool isDestroyed = false;

public:
	virtual void reset() = 0;
	virtual void touch() = 0;
	virtual void update(float deltaTime) = 0;

	void init(Mesh *mesh, glm::vec3 center, glm::vec3 scale, glm::vec3 color);
	Mesh *getMesh();
	glm::mat4 getModelMatrix();
	glm::vec3 getColor();
	glm::vec3 getCenter();
	glm::vec3 getScale();
	bool getIsDestroyed();
	bool setIsDestroyed(bool destroyed);

};