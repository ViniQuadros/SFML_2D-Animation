#include "Player.h"

Player::Player(b2WorldId& worldId)
	: Character(worldId)
{
	m_IdleTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Idle.png");
	m_WalkTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Walk.png");
	m_AttackTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Attack01.png");
	m_HurtTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Hurt.png");
	m_DeathTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Death.png");
	m_Sprite.setTexture(m_IdleTexture);

    b2Body_SetTransform(m_Body, { 3.f, 8.f }, (b2Rot)0.0f);
}

void Player::update(float deltaTime)
{   
	attack(deltaTime);

	if (!m_IsAttacking)
		movement(deltaTime);

	b2Vec2 pos = b2Body_GetPosition(m_Body);

	m_Sprite.setPosition({
		pos.x * 30,
		pos.y * 30
		});
}

void Player::updateAnimation(float deltaTime)
{
    if (m_IsMoving)
    {
        if (m_CurrentState != Walk)
            changeState(Walk);

        m_WalkAnimation.update(deltaTime);
        m_WalkAnimation.applyToSprite(m_Sprite);
    }
    else
    {
        if (m_CurrentState != Idle)
            changeState(Idle);

        m_IdleAnimation.update(deltaTime);
        m_IdleAnimation.applyToSprite(m_Sprite);
    }

    float flip = m_isFacingLeft ? -m_Scale : m_Scale;
    m_Sprite.setScale({ flip, m_Scale });
}

void Player::movement(float deltaTime)
{
    if (m_KnockbackTimer > 0)
        return;

    float speed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)
        ? m_RunningSpeed
        : m_Speed;

    b2Vec2 velocity = { 0.0f, 0.0f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
        velocity.y -= 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
        velocity.y += 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
    {
        velocity.x -= 1.0f;
        m_isFacingLeft = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
    {
        velocity.x += 1.0f;
        m_isFacingLeft = false;
    }

    m_IsMoving = (velocity.x != 0 || velocity.y != 0);

    if (m_IsMoving)
    {
        float length = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity.x /= length;
        velocity.y /= length;

        velocity.x *= speed;
        velocity.y *= speed;
    }

    b2Body_SetLinearVelocity(m_Body, velocity);

    updateAnimation(deltaTime);
}

void Player::attack(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && !m_IsAttacking) {
		m_IsAttacking = true;
		m_AttackAnimation.reset();
	}

	if (m_IsAttacking) {
		if (m_CurrentState != Attack)
			changeState(Attack);
		m_AttackAnimation.update(deltaTime);
		m_AttackAnimation.applyToSprite(m_Sprite);

		if (m_AttackAnimation.isFinished()) {
			m_AttackAnimation.reset();
			m_IsAttacking = false;
		}
	}
}
