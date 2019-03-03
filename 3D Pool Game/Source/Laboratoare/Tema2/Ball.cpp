#include "Ball.h"

Ball::Ball() {
}

Ball::~Ball() {
}

void Ball::reset() {
}

void Ball::touch() {
	//std::cout << "A ball has been touched!" << std::endl;
}

void Ball::velocityAfterFriction()
{
	float dist = this->lastDist * 0.00005f;
	float Ff = this->frictionCt * this->mass * this->gravAcc;
	float vi = glm::length(this->velocity);

	if (vi == 0) {
		return;
	}

	float vfSqr = (-2 * Ff * dist + this->mass * pow(vi, 2)) / this->mass;

	if (vfSqr <= 0) {
		this->velocity = glm::vec3(0);
		return;
	}

	float vf = sqrt(vfSqr);

	this->velocity = glm::normalize(this->velocity) * vf;
}

void Ball::update(float deltaTime) {
	this->velocity = (this->velocity / oldDeltaTime) * deltaTime;
	oldDeltaTime = deltaTime;
	setLocation(velocity.x, velocity.y, velocity.z);

	lastDist = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.z, 2));
	velocityAfterFriction();
}

void Ball::setBallType(int type)
{
	this->ballType = type;
}

int Ball::getBallType()
{
	return this->ballType;
}

void Ball::setVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}

glm::vec3 Ball::getVelocity()
{
	return this->velocity;
}

void Ball::setLocation(float x, float y, float z)
{
	glm::mat4 translate = glm::mat4(1);
	this->modelMatrix = glm::translate(translate, glm::vec3(x, y, z)) * this->modelMatrix;

	center.x += x;
	center.y += y;
	center.z += z;
}

int Ball::checkCollisionHole(Object* hole)
{
	glm::vec3 distanceVec = hole->getCenter() - center;
	float dist = glm::length(distanceVec);

	if (dist <= scale.x / 2 + hole->getScale().x / 2) {
		//std::cout << "Hole Collision" << std::endl;
		isDestroyed = true;
		this->velocity = glm::vec3(0);
		return ballType;
	}

	return -1;
}

void Ball::checkCollisionWall(Object* wall)
{
	float downX = wall->getCenter().x - wall->getScale().x / 2;
	float downZ = wall->getCenter().z - wall->getScale().z / 2;
	float upX = wall->getCenter().x + wall->getScale().x / 2;
	float upZ = wall->getCenter().z + wall->getScale().z / 2;

	float closestX = std::max(downX, std::min(center.x, upX)); // closest point on the rectangle
	float closestZ = std::max(downZ, std::min(center.z, upZ));

	glm::vec3 distanceVec = center - glm::vec3(closestX, center.y, closestZ);
	float dist = glm::length(distanceVec);

	if (dist <= scale.x / 2) { // check for collision
		if (closestX == center.x && closestZ > center.z) { // check where did the ball collide with the rectangle
			this->velocity = glm::vec3(velocity.x, 0, -fabs(velocity.z));
			wall->touch();
		}
		else if (closestX == center.x && closestZ < center.z) { // check where did the ball collide with the rectangle
			this->velocity = glm::vec3(velocity.x, 0, fabs(velocity.z));
			wall->touch();
		}
		else if (closestZ == center.z && closestX > center.x) {
			this->velocity = glm::vec3(-fabs(velocity.x), 0, velocity.z);
			wall->touch();
		}
		else if (closestZ == center.z && closestX < center.x) {
			this->velocity = glm::vec3(fabs(velocity.x), 0, velocity.z);
			wall->touch();
		}
	}
}

bool Ball::checkCollisionBall(Ball* other)
{
	glm::vec3 vel = this->velocity - other->getVelocity(); // transform second ball in a static 
	glm::vec3 distanceVector = other->getCenter() - this->getCenter();
	float distanceBetween = glm::length(distanceVector) - 2 * (this->getScale().x / 2);
	float velocityLength = glm::length(vel);

	if (velocityLength == 0) {
		return false;
	}

	if (velocityLength < distanceBetween) {
		return false;
	}

	glm::vec3 normalVel = glm::normalize(vel);
	float isMovingTowardsBall = glm::dot(normalVel, distanceVector);
	if (isMovingTowardsBall <= 0) {
		return false;
	}
	float closestPoint = glm::dot(distanceVector, normalVel);
	float distVelCenterSqr = glm::length2(distanceVector) - pow(closestPoint, 2);

	if (pow(this->getScale().x, 2) <= distVelCenterSqr) {
		return false;
	}

	float distanceAfterContact = pow(this->getScale().x, 2) - distVelCenterSqr;
	float distanceUntilContact = closestPoint - sqrt(distanceAfterContact);

	glm::vec3 shortenedVel = glm::normalize(vel);
	shortenedVel *= distanceUntilContact; // move until the two balls touch

	float velScale = glm::length(shortenedVel) / velocityLength;

	this->setLocation(velocity.x * velScale, 0, velocity.z * velScale);
	other->setLocation(other->getVelocity().x * velScale, 0, other->getVelocity().z * velScale);

	other->touch();

	return true;
}

void Ball::bounce(Ball* other)
{
	glm::vec3 collisionVec = glm::normalize(this->center - other->getCenter());

	float ball1Speed = glm::dot(this->velocity, collisionVec);
	float ball2Speed = glm::dot(other->getVelocity(), collisionVec);

	float optimizedP = (2.0 * (ball1Speed - ball2Speed)) / (2 * this->mass);

	glm::vec3 newVel1 = this->velocity - optimizedP * this->mass * collisionVec;
	glm::vec3 newVel2 = other->getVelocity() +  optimizedP * this->mass * collisionVec;

	this->velocity = newVel1;
	other->setVelocity(newVel2);
}
