#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();

	void update(float deltaTime) override;

private:

};