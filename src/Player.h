#pragma once
#include "Character.h"
#include <algorithm>

class Player : public Character
{
public:
	Player(b2WorldId& worldId);

	void update(float deltaTime) override;
	void updateAnimation(float deltaTime);
	void movement(float deltaTime);
	void attack(float deltaTime);

private:
	float m_Speed = 5.f;
	float m_RunningSpeed = 10.0f;
};