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

		m_HurtAnimation.setFrameSize({ 100,100 });
		m_HurtAnimation.setFrameCount(6);
		m_HurtAnimation.setFrameTime(0.15f);
		m_HurtAnimation.setLoop(false);

		m_DeathAnimation.setFrameSize({ 100,100 });
		m_DeathAnimation.setFrameCount(6);
		m_DeathAnimation.setFrameTime(0.2f);
		m_DeathAnimation.setLoop(false);

		changeState(Idle);
}

void Character::update(float deltaTime) {

}

void Character::draw(sf::RenderWindow& window)
{
	window.draw(m_Sprite);
}

void Character::takeDamage(int damage, float deltaTime)
{
	m_Health -= damage;
	//if (m_Health <= 0) {
	//	m_DeathAnimation.update(deltaTime);
	//	m_DeathAnimation.applyToSprite(m_Sprite);
	//}
	//else {
	//	m_HurtAnimation.update(deltaTime);
	//	m_HurtAnimation.applyToSprite(m_Sprite);
	//}
}

bool Character::isColliding(const sf::FloatRect& other) const
{
	return getCharBounds().findIntersection(other).has_value();
}

const sf::FloatRect Character::getCharBounds() const
{
	return m_Sprite.getGlobalBounds();
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
