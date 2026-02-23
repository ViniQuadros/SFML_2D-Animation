#include "Character.h"

Character::Character() {
		setTexture("CharactersSprites/Soldier/Soldier/Soldier-Idle.png");
		auto bounds = m_Sprite.getLocalBounds();
		m_Sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
		m_Sprite.setScale(sf::Vector2f(m_Scale, m_Scale));

		m_IdleAnimation.setFrameSize({ 100,100 });
		m_IdleAnimation.setFrameCount(6);
		m_IdleAnimation.setFrameTime(0.15f);

		m_WalkAnimation.setFrameSize({ 100,100 });
		m_WalkAnimation.setFrameCount(8);
		m_WalkAnimation.setFrameTime(0.15f);
}

const sf::Sprite& Character::getCharSprite() const
{
	return m_Sprite;
}

void Character::update(float deltaTime)
{
	movement(deltaTime);
}

void Character::draw(sf::RenderWindow& window)
{
	window.draw(m_Sprite);
}

void Character::movement(float deltaTime)
{
	isMoving = false;
	float movementSpeed = m_Speed * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)) {
		movementSpeed = m_RunningSpeed * deltaTime;
	}

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
		m_Sprite.setScale({-m_Scale,m_Scale});
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		m_Position.x += movementSpeed;
		m_Sprite.setScale({ m_Scale,m_Scale });
		isMoving = true;
	}

	m_Sprite.setPosition(m_Position);

	if (isMoving) {
		setTexture("CharactersSprites/Soldier/Soldier/Soldier-Walk.png");

		m_WalkAnimation.update(deltaTime);
		m_WalkAnimation.applyToSprite(m_Sprite);
	}
	else {
		setTexture("CharactersSprites/Soldier/Soldier/Soldier-Idle.png");

		m_IdleAnimation.update(deltaTime);
		m_IdleAnimation.applyToSprite(m_Sprite);
	}
}

void Character::setPosition(sf::Vector2f position)
{
	m_Position = position;
	m_Sprite.setPosition(position);
}

void Character::setTexture(std::string filePath)
{
	if (m_Texture.loadFromFile(filePath)) {
		m_Sprite.setTexture(m_Texture);
		m_Sprite.setTextureRect(sf::IntRect(
			{ 0, 0 },
			{ 100, 100 }
		));
	}
}
