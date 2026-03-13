#include "Player.h"

Player::Player()
{
	m_IdleTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Idle.png");
	m_WalkTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Walk.png");
	m_AttackTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Attack01.png");
	m_HurtTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Hurt.png");
	m_DeathTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Death.png");
	m_Sprite.setTexture(m_IdleTexture);

	m_Position = { 100, 250 };
	m_Sprite.setPosition(m_Position);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
		m_Position.y -= movementSpeed;
		m_IsMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
		m_Position.y += movementSpeed;
		m_IsMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		m_Position.x -= movementSpeed;
		m_isFacingLeft = true;
		m_IsMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		m_Position.x += movementSpeed;
		m_isFacingLeft = false;
		m_IsMoving = true;
	}

	m_Sprite.setPosition(m_Position);

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
