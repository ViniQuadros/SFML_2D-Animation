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

		virtual void update(float deltaTime);
		void draw(sf::RenderWindow& window);
		void takeDamage(int damage, float deltaTime);
		bool isColliding(const sf::FloatRect& other) const;
		const sf::FloatRect getCharBounds() const;

		void changeState(AnimationStates newState);

		const sf::Sprite& getCharSprite() const;

	protected:
		int m_Health = 30;

		float m_Scale = 3.f;
		bool isMoving = false;
		bool m_isFacingLeft = false;
		bool m_ShiftHeld = false;
		bool isAttacking = false;

		sf::Vector2f m_Position;

		AnimationStates currentState = Idle;
		sf::Texture m_IdleTexture;
		sf::Texture m_WalkTexture;
		sf::Texture m_AttackTexture;
		sf::Texture m_HurtTexture;
		sf::Texture m_DeathTexture;
		sf::Sprite m_Sprite = sf::Sprite(m_IdleTexture);
		Animation m_IdleAnimation;
		Animation m_WalkAnimation;
		Animation m_AttackAnimation;
		Animation m_HurtAnimation;
		Animation m_DeathAnimation;

	private:
};