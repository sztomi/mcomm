#include "precompiled.h"
#include "spriteanimationsystem.h"

#include "simulation/components/animationframescomponent.h"
#include "simulation/components/spritecomponent.h"

namespace mcomm
{

SpriteAnimationSystem::SpriteAnimationSystem()
	: m_currentFrameIndex(0), m_forward(true), m_isRunning(false)
{ }

void SpriteAnimationSystem::update(float dt)
{
	if (!m_isRunning) return;

	auto frames = m_parent->COMPONENT(AnimationFrames);
	auto currentFrame = frames->frame(m_currentFrameIndex);

	if (clock.getElapsedTime().asMilliseconds() > currentFrame.frameLength())
	{
		if (m_forward)
		{
			if (m_currentFrameIndex + 1 < frames->frameCount())
			{
				++m_currentFrameIndex;
			}
			else
			{
				m_forward = false;
				--m_currentFrameIndex;
			}
		}
		else
		{
			if (m_currentFrameIndex - 1 >= 0)
			{
				--m_currentFrameIndex;
			}
			else
			{
				m_forward = true;
				++m_currentFrameIndex;
			}
		}

		applyFrame();

		clock.restart();
	}
}

void SpriteAnimationSystem::applyFrame()
{
	auto frames = m_parent->COMPONENT(AnimationFrames);
	auto nextFrame = frames->frame(m_currentFrameIndex);
	auto sprite = m_parent->COMPONENT(Sprite);
	sprite->setSpriteCoordX(nextFrame.texCoordX());
	sprite->setSpriteCoordY(nextFrame.texCoordY());
}

void SpriteAnimationSystem::stopAt(int frame)
{
	m_isRunning = false;
	m_currentFrameIndex = frame;
	applyFrame();
}

void SpriteAnimationSystem::startFrom(int frame)
{
	m_currentFrameIndex = frame;
	m_isRunning = true;
	applyFrame();
}

bool SpriteAnimationSystem::isRunning() const
{
	return m_isRunning;
}

}
