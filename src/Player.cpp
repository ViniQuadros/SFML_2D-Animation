#include "Player.h"

Player::Player()
{
	m_IdleTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Idle.png");
	m_WalkTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Walk.png");
	m_AttackTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Attack01.png");
	m_Sprite.setTexture(m_IdleTexture);

	m_Position = { 100, 250 };
	m_Sprite.setPosition(m_Position);
}

void Player::update(float deltaTime)
{
	attack(deltaTime);
	if (!isAttacking) {
		movement(deltaTime);
	}
}

void Player::movement(float deltaTime)
{
	isMoving = false;
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
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
		m_Position.y += movementSpeed;
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		m_Position.x -= movementSpeed;
		m_isFacingLeft = true;
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		m_Position.x += movementSpeed;
		m_isFacingLeft = false;
		isMoving = true;
	}

	m_Sprite.setPosition(m_Position);

	//Select proper sprite animations of movement
	if (isMoving)
	{
		if (currentState != Walk)
			changeState(Walk);

		m_WalkAnimation.update(deltaTime);
		m_WalkAnimation.applyToSprite(m_Sprite);
	}
	else {
		if (currentState != Idle)
			changeState(Idle);

		m_IdleAnimation.update(deltaTime);
		m_IdleAnimation.applyToSprite(m_Sprite);
	}

	float flip = m_isFacingLeft ? -m_Scale : m_Scale;
	m_Sprite.setScale({ flip, m_Scale });
}

void Player::attack(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && !isAttacking) {
		isAttacking = true;
		m_AttackAnimation.reset();
	}

	if (isAttacking) {
		if (currentState != Attack)
			changeState(Attack);
		m_AttackAnimation.update(deltaTime);
		m_AttackAnimation.applyToSprite(m_Sprite);

		if (m_AttackAnimation.isFinished()) {
			m_AttackAnimation.reset();
			isAttacking = false;
		}
	}
}
