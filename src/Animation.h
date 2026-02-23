#pragma once
#include <SFML/Graphics.hpp>

class Animation {
	public:
		Animation();

		void update(float deltaTime);
		void applyToSprite(sf::Sprite& sprite);

		void setFrameSize(sf::Vector2i size);
		void setFrameCount(int count);
		void setFrameTime(float time);

	private:
		sf::Vector2i m_FrameSize;
		int m_FrameCount;
		float m_FrameTime;

		float m_CurrentTime;
		int m_CurrentFrame;
};