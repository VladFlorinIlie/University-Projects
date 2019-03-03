#include "Player.h"

Player::Player(int id)
{
	this->playerId = id;
}

Player::~Player()
{
}

int Player::getPlayerId()
{
	return this->playerId;
}

void Player::setBallType(int type)
{
	this->ballType = type;
}

void Player::setNoOfBalls(int no)
{
	this->noOfBalls = no;
}

int Player::getBallType()
{
	return this->ballType;
}

int Player::getNoOfBalls()
{
	return this->noOfBalls;
}
