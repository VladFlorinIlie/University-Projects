#pragma once

class Player {

private:
	int playerId;
	int ballType = -1;
	int noOfBalls = 0;

public:
	Player(int id);
	~Player();

	int getPlayerId();
	void setBallType(int type);
	void setNoOfBalls(int no);
	int getBallType();
	int getNoOfBalls();

};