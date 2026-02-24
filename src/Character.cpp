#include "Character.h"

Character::Character() {
		m_IdleTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Idle.png");
		m_WalkTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Walk.png");
		m_AttackTexture.loadFromFile("CharactersSprites/Soldier/Soldier/Soldier-Attack01.png");
		m_Sprite.setTexture(m_IdleTexture);

		m_Sprite.setPosition(m_Position);
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

void Character::update(float deltaTime)
{
	attack(deltaTime);
	if (!isAttacking) {
		movement(deltaTime);
	}

	//DEBUGGING
	//std::cout << "********************" "\n";
	//std::cout << "X" << m_Position.x << "\n";
	//std::cout << "Y" << m_Position.y << "\n";
	//std::cout << "X" << m_Sprite.getOrigin().x << "\n";
	//std::cout << "Y" << m_Sprite.getOrigin().y << "\n";
	//std::cout << "********************" "\n";
}

void Character::draw(sf::RenderWindow& window)
{
	window.draw(m_Sprite);
}

void Character::movement(float deltaTime)
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

void Character::attack(float deltaTime)
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
