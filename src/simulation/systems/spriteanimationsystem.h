#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class SpriteAnimationSystem : public System
{
    RTTI()
public:
    SpriteAnimationSystem();
	GET bool isRunning() const;

	void update(float dt) override;
	void stopAt(int frame);
	void startFrom(int frame);

private:
	void applyFrame();

private:
	int m_currentFrameIndex;
	bool m_forward; //< is the animation running forward?
	bool m_isRunning;
	sf::Clock clock;
};

}
REFLECT_TYPE(mcomm::SpriteAnimationSystem)
