#pragma once
#include <SFML/Graphics.hpp>

class Animation {
	public:
		Animation();

		void update(float deltaTime);
		void reset();
		void applyToSprite(sf::Sprite& sprite);
		void setLoop(bool loop); //Check if animation is a loop or not
		bool isFinished();

		//Define initial values for the sprite sheet
		void setFrameSize(sf::Vector2i size);
		void setFrameCount(int count);
		void setFrameTime(float time);

		const sf::Vector2i& getFrameSize() const;

	private:
		sf::Vector2i m_FrameSize;
		int m_FrameCount;
		float m_FrameTime;

		bool m_isLoop = true;
		bool m_isFinished = false;

		float m_CurrentTime;
		int m_CurrentFrame;
};