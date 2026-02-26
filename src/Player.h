#pragma once
#include "Character.h"
#include <algorithm>

class Player : public Character
{
public:
	Player();

	void update(float deltaTime) override;
	void movement(float deltaTime);
	void attack(float deltaTime);

private:
	float m_Speed = 20.f;
	float m_RunningSpeed = 50.0f;
};