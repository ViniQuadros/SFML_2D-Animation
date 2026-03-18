#pragma once

#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <iostream>
#include "box2d/box2d.h"

enum AnimationStates {
	Idle,
	Walk,
	Attack,
	Hurt,
	Death
};

class Character {
	public:
		Character(b2WorldId& worldId);

		virtual void update(float deltaTime);
		void draw(sf::RenderWindow& window);

		void takeDamage(int damage, float deltaTime);
		void knockback();

		bool isColliding(const sf::FloatRect& other) const;

		void changeState(AnimationStates newState);

		const sf::Sprite& getCharSprite() const;
		const sf::FloatRect getCharBounds() const;
		const int GetCharDamage() const;

	protected:
		b2WorldId& m_WorldId;
		b2BodyId m_Body;
		b2BodyDef bodyDef = b2DefaultBodyDef();

		int m_Health = 30;
		int m_Damage = 10;
		float m_DamageCooldown = 0.0f;
		const float m_InvencibilityDuration = 0.5f;
		float m_KnockbackTimer = 0.0f;
		const float m_StunDuration = 0.25f;

		float m_Scale = 3.f;
		bool m_IsMoving = false;
		bool m_isFacingLeft = false;
		bool m_ShiftHeld = false;
		bool m_IsAttacking = false;

		sf::Vector2f m_Position;

		AnimationStates m_CurrentState = Idle;
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
};