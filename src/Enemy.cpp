#include "Enemy.h"

Enemy::Enemy(b2WorldId& worldId)
	: Character(worldId)
{
	m_IdleTexture.loadFromFile("CharactersSprites/Orc/Orc/Orc-Idle.png");
	m_WalkTexture.loadFromFile("CharactersSprites/Orc/Orc/Orc-Walk.png");
	m_AttackTexture.loadFromFile("CharactersSprites/Orc/Orc/Orc-Attack01.png");
	m_HurtTexture.loadFromFile("CharactersSprites/Orc/Orc/Orc-Hurt.png");
	m_DeathTexture.loadFromFile("CharactersSprites/Orc/Orc/Orc-Death.png");
	m_Sprite.setTexture(m_IdleTexture);

	m_Position = { 400, 250 };
	m_Sprite.setPosition(m_Position);
}

void Enemy::update(float deltaTime)
{
	if (m_CurrentState != Idle)
		changeState(Idle);

	m_IdleAnimation.update(deltaTime);
	m_IdleAnimation.applyToSprite(m_Sprite);
}
