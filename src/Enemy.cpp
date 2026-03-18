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

	b2Body_SetTransform(m_Body, { 400.f / 30.f, 250.f / 30.f }, b2Rot_identity);

	//m_Position = { 400, 250 };
	//m_Sprite.setPosition(m_Position);
}

void Enemy::update(float deltaTime)
{
	Character::update(deltaTime);

	b2Vec2 pos = b2Body_GetPosition(m_Body);
	m_Sprite.setPosition({ pos.x * 30.f, pos.y * 30.f });

	if (m_CurrentState != Idle)
		changeState(Idle);

	m_IdleAnimation.update(deltaTime);
	m_IdleAnimation.applyToSprite(m_Sprite);
}
