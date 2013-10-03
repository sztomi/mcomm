#pragma once

#include <SFML/System/Clock.hpp>
#include "simulation/system.h"

namespace mcomm
{

class SpriteAnimationSystem : public System
{
public:
	SpriteAnimationSystem();

	void init(const pugi::xml_node& xml);
	std::string toString() const;
	bool isRunning() const;

	void update(float dt);
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