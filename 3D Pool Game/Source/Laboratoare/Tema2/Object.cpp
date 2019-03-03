#include "Object.h"

void Object::init(Mesh * mesh, glm::vec3 center, glm::vec3 scale, glm::vec3 color)
{
	this->mesh = mesh;
	this->center = center;
	this->scale = scale;
	this->color = color;

	glm::mat4 modelMat = glm::mat4(1);
	modelMat = glm::translate(modelMat, center);
	modelMat = glm::scale(modelMat, scale);

	this->modelMatrix = modelMat;
}

Mesh* Object::getMesh() {
	return mesh;
}

glm::mat4 Object::getModelMatrix() {
	return modelMatrix;
}

glm::vec3 Object::getCenter() {
	return center;
}

glm::vec3 Object::getScale() {
	return scale;
}

glm::vec3 Object::getColor() {
	return color;
}

bool Object::getIsDestroyed()
{
	return isDestroyed;
}

bool Object::setIsDestroyed(bool destroyed)
{
	return this->isDestroyed = destroyed;
}
