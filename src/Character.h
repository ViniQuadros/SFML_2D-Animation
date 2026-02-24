#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <iostream>

enum AnimationStates {
	Idle,
	Walk,
	Attack
};

class Character {
	public:
		Character();

		void update(float deltaTime);
		void draw(sf::RenderWindow& window);

		void movement(float deltaTime);
		void attack(float deltaTime);
		void changeState(AnimationStates newState);

		const sf::Sprite& getCharSprite() const;

	private:
		float m_Scale = 3.f;
		bool isMoving = false;
		bool m_isFacingLeft = false;
		bool m_ShiftHeld = false;
		bool isAttacking = false;

		sf::Vector2f m_Position = {100.f, 250.f};
		float m_Speed = 10.f;
		float m_RunningSpeed = 50.0f;

		AnimationStates currentState = Idle;
		sf::Texture m_IdleTexture;
		sf::Texture m_WalkTexture;
		sf::Texture m_AttackTexture;
		sf::Sprite m_Sprite = sf::Sprite(m_IdleTexture);
		Animation m_IdleAnimation;
		Animation m_WalkAnimation;
		Animation m_AttackAnimation;
};