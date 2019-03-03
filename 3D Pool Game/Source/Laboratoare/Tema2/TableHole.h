#pragma once

#include "Object.h"

class TableHole : public Object {

public:
	TableHole();
	~TableHole();

	void reset();
	void touch();
	void update(float deltaTime);

};