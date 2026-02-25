#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player();

	void update(float deltaTime) override;
	void movement(float deltaTime);
	void attack(float deltaTime);

private:
	float m_Speed = 10.f;
	float m_RunningSpeed = 50.0f;
};