#include "Player.h"

Player::Player(b2WorldId& worldId)
{
	m_IdleTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Idle.png");
	m_WalkTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Walk.png");
	m_AttackTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Attack01.png");
	m_HurtTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Hurt.png");
	m_DeathTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Death.png");
	m_Sprite.setTexture(m_IdleTexture);

	m_Position = { 100, 250 };
	m_Sprite.setPosition(m_Position);

	bodyDef.position = { 100.0f, 250.0f };
	m_Body = b2CreateBody(worldId, &bodyDef);
}

void Player::update(float deltaTime)
{
	attack(deltaTime);
	if (!m_IsAttacking) {
		movement(deltaTime);
	}
}

void Player::movement(float deltaTime)
{
	m_IsMoving = false;
	float movementSpeed = m_Speed * deltaTime;

	//Sprinting Logic
	bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift);
	if (shiftPressed) {
		movementSpeed = m_RunningSpeed * deltaTime;
		m_WalkAnimation.setFrameTime(.05f);
	}
	if (!shiftPressed && m_ShiftHeld) {
		m_WalkAnimation.setFrameTime(0.15f);
	}
	m_ShiftHeld = shiftPressed;

	//Movement inputs
	// 1. Check if we are currently being knocked back (stunned)
	// If you haven't added m_KnockbackTimer yet, do so in update()
	if (m_KnockbackTimer > 0) return;

	m_IsMoving = false;
	b2Vec2 velocity = { 0.0f, 0.0f };
	float speed = shiftPressed ? m_RunningSpeed : m_Speed;

	// 2. Set velocity vectors instead of positions
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) velocity.y -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) velocity.y += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		velocity.x -= speed;
		m_isFacingLeft = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		velocity.x += speed;
		m_isFacingLeft = false;
	}

	if (velocity.x != 0 || velocity.y != 0) m_IsMoving = true;

	// 3. Apply velocity to the Box2D body
	b2Body_SetLinearVelocity(m_Body, velocity);

	// 4. SYNC: Make the Sprite follow the Physics Body
	b2Vec2 physicsPos = b2Body_GetPosition(m_Body);
	m_Sprite.setPosition({ physicsPos.x, physicsPos.y });

	//Screen Borders
	if (m_Position.x > 800 - m_Sprite.getOrigin().x / 2.f) {
		m_Position.x = 800 - m_Sprite.getOrigin().x / 2.f;
	}
	//Left
	if (m_Position.x < m_Sprite.getOrigin().x / 2.f) {
		m_Position.x = m_Sprite.getOrigin().x / 2.f;
	}
	if (m_Position.y > 600 - m_Sprite.getOrigin().x / 2.f) {
		m_Position.y = 600 - m_Sprite.getOrigin().x / 2.f;
	}
	//Top
	if (m_Position.y < m_Sprite.getOrigin().x / 2.f) {
		m_Position.y = m_Sprite.getOrigin().x / 2.f;
	}

	//Select proper sprite animations of movement
	if (m_IsMoving)
	{
		if (m_CurrentState != Walk)
			changeState(Walk);

		m_WalkAnimation.update(deltaTime);
		m_WalkAnimation.applyToSprite(m_Sprite);
	}
	else {
		if (m_CurrentState != Idle)
			changeState(Idle);

		m_IdleAnimation.update(deltaTime);
		m_IdleAnimation.applyToSprite(m_Sprite);
	}

	float flip = m_isFacingLeft ? -m_Scale : m_Scale;
	m_Sprite.setScale({ flip, m_Scale });
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
