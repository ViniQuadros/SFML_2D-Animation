#include "Character.h"

Character::Character() {
		m_Sprite.setScale({ m_Scale,m_Scale });
		m_Sprite.setOrigin({ 50.f,50.f });

		m_IdleAnimation.setFrameSize({ 100,100 });
		m_IdleAnimation.setFrameCount(6);
		m_IdleAnimation.setFrameTime(0.15f);
		m_IdleAnimation.setLoop(true);

		m_WalkAnimation.setFrameSize({ 100,100 });
		m_WalkAnimation.setFrameCount(8);
		m_WalkAnimation.setFrameTime(0.15f);
		m_WalkAnimation.setLoop(true);

		m_AttackAnimation.setFrameSize({ 100,100 });
		m_AttackAnimation.setFrameCount(6);
		m_AttackAnimation.setFrameTime(0.1f);
		m_AttackAnimation.setLoop(false);

		changeState(Idle);
}

void Character::update(float deltaTime){

}

void Character::draw(sf::RenderWindow& window)
{
	window.draw(m_Sprite);
}

void Character::changeState(AnimationStates newState)
{
	if (currentState == newState) return;

	switch (newState) {
		case Idle: m_Sprite.setTexture(m_IdleTexture); break;
		case Walk: m_Sprite.setTexture(m_WalkTexture); break;
		case Attack: m_Sprite.setTexture(m_AttackTexture); break;
		default: break;
	}

	m_Sprite.setOrigin({50.f, 50.f});
	currentState = newState;
}

const sf::Sprite& Character::getCharSprite() const
{
	return m_Sprite;
}
