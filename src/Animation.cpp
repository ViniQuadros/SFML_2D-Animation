#include "Animation.h"

Animation::Animation()
	: m_FrameSize({ 0,0 }),
	  m_FrameCount(0),
	  m_FrameTime(0.1f),
	  m_CurrentTime(0.f),
	  m_CurrentFrame(0)
{
}

void Animation::update(float deltaTime)
{
	m_CurrentTime += deltaTime;

	if (m_CurrentTime >= m_FrameTime) {
		m_CurrentTime = 0.0f;
		m_CurrentFrame++;

		if (m_CurrentFrame >= m_FrameCount) {
			m_CurrentFrame = 0;
		}
	}
}

void Animation::applyToSprite(sf::Sprite& sprite)
{
	sprite.setTextureRect(sf::IntRect({ m_CurrentFrame * m_FrameSize.x, 0 },
		m_FrameSize)
	);
}

void Animation::setFrameSize(sf::Vector2i size)
{
	m_FrameSize = size;
}

void Animation::setFrameCount(int count)
{
	m_FrameCount = count;
}

void Animation::setFrameTime(float time)
{
	m_FrameTime = time;
}
