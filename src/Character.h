#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <iostream>

class Character {
	public:
		Character();

		void update(float deltaTime);
		void draw(sf::RenderWindow& window);

		void movement(float deltaTime);

		void setTexture(std::string filePath);
		void setPosition(sf::Vector2f position);

		const sf::Sprite& getCharSprite() const;

	private:
		float m_Scale = 3.f;

		sf::Texture m_Texture;
		sf::Sprite m_Sprite = sf::Sprite(m_Texture);

		sf::Vector2f m_Position;
		bool isMoving;
		float m_Speed = 10.f;
		float m_RunningSpeed = 50.0f;

		Animation m_IdleAnimation;
		Animation m_WalkAnimation;
};