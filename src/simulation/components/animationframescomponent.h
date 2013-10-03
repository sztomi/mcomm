#pragma once

#include <vector>

#include "media/animationframe.h"
#include "simulation/component.h"

namespace mcomm
{

class AnimationFramesComponent : public Component
{
public:
	AnimationFramesComponent();

	std::string toString() const;
	void init(const pugi::xml_node& xml);

	int frameCount() const;
	
	void addFrame(const AnimationFrame& frame);
	AnimationFrame frame(int index);

private:
	std::vector<AnimationFrame> m_frames;
};

}