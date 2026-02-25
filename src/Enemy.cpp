#include "Enemy.h"

Enemy::Enemy()
{
	m_IdleTexture.loadFromFile("CharactersSprites/Orc/Orc/Orc-Idle.png");
	m_WalkTexture.loadFromFile("CharactersSprites/Orc/Orc/Orc-Walk.png");
	m_AttackTexture.loadFromFile("CharactersSprites/Orc/Orc/Orc-Attack01.png");
	m_Sprite.setTexture(m_IdleTexture);

	m_Position = { 400, 250 };
	m_Sprite.setPosition(m_Position);
}

void Enemy::update(float deltaTime)
{
	if (currentState != Idle)
		changeState(Idle);

	m_IdleAnimation.update(deltaTime);
	m_IdleAnimation.applyToSprite(m_Sprite);
}
