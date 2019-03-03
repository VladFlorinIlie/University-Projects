#include "Stick.h"

Stick::Stick()
{
}

Stick::~Stick()
{
}

void Stick::reset()
{
}

void Stick::touch()
{
}

void Stick::update(float deltaTime)
{
}

void Stick::setCenter(glm::vec3 center)
{
	glm::mat4 translate = glm::mat4(1);
	this->modelMatrix = glm::translate(translate, center - this->center) * this->modelMatrix;
	this->rotatedMat = this->modelMatrix;

	this->center = center;
}

void Stick::spinAround(glm::vec3 ballPos, float degree)
{
	glm::mat4 matr = glm::mat4(1);
	matr = glm::translate(matr, ballPos);
	matr = glm::rotate(matr, degree, glm::vec3(0, 1, 0));
	matr = glm::translate(matr, -ballPos);
	this->rotatedMat = matr * this->rotatedMat;
}

glm::mat4 Stick::getRotatedMat()
{
	return this->rotatedMat;
}
