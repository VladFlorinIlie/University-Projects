#pragma once

#include "Object.h"

class Table : public Object {

public:
	Table();
	~Table();

	void reset() override;
	void touch() override;
	void update(float deltaTime) override;

};