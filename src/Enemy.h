#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(b2WorldId& worldId);

	void update(float deltaTime) override;

private:

};