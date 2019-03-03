#pragma once

#include "Object.h"

class TableWall : public Object {

public:
	TableWall();
	~TableWall();

	void reset();
	void touch();
	void update(float deltaTime);

};