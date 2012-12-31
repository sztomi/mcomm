#include "animationframescomponent.h"
#include "pugixml.hpp"

namespace mcomm
{

AnimationFramesComponent::AnimationFramesComponent()
{

}

std::string AnimationFramesComponent::toString() const
{
	return "AnimationFramesComponent";
}

int AnimationFramesComponent::frameCount() const
{
	return m_frames.size();
}

void AnimationFramesComponent::addFrame(const AnimationFrame& frame)
{
	m_frames.push_back(frame);
}

AnimationFrame AnimationFramesComponent::frame(int index)
{
	return m_frames[index];
}

void AnimationFramesComponent::init(const pugi::xml_node& xml)
{
	const std::string n("AnimationFrame");
	for (auto& child : xml.children())
	{
		if (n == child.name())
		{
			addFrame(AnimationFrame(child));
		}
	}
}




}