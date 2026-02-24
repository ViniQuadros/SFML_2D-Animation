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
    if (m_isFinished) return;

    m_CurrentTime += deltaTime;

    if (m_CurrentTime >= m_FrameTime)
    {
        m_CurrentTime = 0.f;
        m_CurrentFrame++;

        if (m_CurrentFrame >= m_FrameCount)
        {
            if (m_isLoop)
            {
                m_CurrentFrame = 0;
            }
            else
            {
                m_CurrentFrame = m_FrameCount - 1;
                m_isFinished = true;
            }
        }
    }
}

void Animation::applyToSprite(sf::Sprite& sprite)
{
    sprite.setTextureRect(sf::IntRect(
        { m_CurrentFrame * m_FrameSize.x, 0 },
        m_FrameSize
    ));
}

void Animation::reset()
{
	m_CurrentFrame = 0;
	m_CurrentTime = 0.0f;
    m_isFinished = false;
}

void Animation::setLoop(bool loop)
{
    m_isLoop = loop;
}

bool Animation::isFinished()
{
	return m_isFinished;
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

const sf::Vector2i& Animation::getFrameSize() const
{
    return m_FrameSize;
}
