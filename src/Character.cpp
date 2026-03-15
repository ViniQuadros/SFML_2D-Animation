#include "Character.h"

Character::Character(b2WorldId& worldId) : m_WorldId(worldId) {
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

		m_WorldId = worldId;
		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 5.0f;
		m_Body = b2CreateBody(worldId, &bodyDef);

		b2Polygon box = b2MakeBox(0.5f, 0.5f);
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 1.0f;
		b2CreatePolygonShape(m_Body, &shapeDef, &box);
}

void Character::update(float deltaTime) {
	if (m_DamageCooldown > 0) {
		m_DamageCooldown -= deltaTime;
	}

	if (m_KnockbackTimer > 0) {
		m_KnockbackTimer -= deltaTime;
	}
}

void Character::draw(sf::RenderWindow& window)
{
	window.draw(m_Sprite);
}

void Character::takeDamage(int damage, float deltaTime)
{
	if (m_DamageCooldown > 0) return;

	m_Health -= damage;
	m_DamageCooldown = m_InvencibilityDuration;

	if (m_Health <= 0) {
		m_DeathAnimation.update(deltaTime);
		m_DeathAnimation.applyToSprite(m_Sprite);
		m_Health = 0;
	}
	else {
		m_HurtAnimation.update(deltaTime);
		m_HurtAnimation.applyToSprite(m_Sprite);

		this->knockback();
	}

	std::cout << this->m_Health << std::endl;
}

void Character::knockback()
{
	if (!b2Body_IsValid(m_Body)) return;

	float knockbackMagnitude = 5.0f;

	b2Vec2 impulse;
	if (m_isFacingLeft) {
		impulse = { knockbackMagnitude, 0.0f };
	}
	else {
		impulse = { -knockbackMagnitude, 0.0f };
	}

	b2Body_SetLinearVelocity(m_Body, { 0.0f, 0.0f });
	b2Body_ApplyLinearImpulseToCenter(m_Body, impulse, true);

	m_KnockbackTimer = 0.25f;
}

bool Character::isColliding(const sf::FloatRect& other) const
{
	return getCharBounds().findIntersection(other).has_value();
}

const sf::FloatRect Character::getCharBounds() const
{
	sf::FloatRect bounds = m_Sprite.getGlobalBounds();

	//Reducing bound size to fit the sprites
	float shrinkX = bounds.size.x * 0.45f;
	float shrinkY = bounds.size.y * 0.43f;  

	return sf::FloatRect(
		{ bounds.position.x + shrinkX, bounds.position.y + shrinkY },
		{ bounds.size.x - shrinkX * 2.f, bounds.size.y - shrinkY * 2.f }
	);
}

void Character::changeState(AnimationStates newState)
{
	if (m_CurrentState == newState) return;

	switch (newState) {
		case Idle: m_Sprite.setTexture(m_IdleTexture); break;
		case Walk: m_Sprite.setTexture(m_WalkTexture); break;
		case Attack: m_Sprite.setTexture(m_AttackTexture); break;
		default: break;
	}

	m_Sprite.setOrigin({50.f, 50.f});
	m_CurrentState = newState;
}

const sf::Sprite& Character::getCharSprite() const
{
	return m_Sprite;
}

const int Character::GetCharDamage() const
{
	return m_Damage;
}
