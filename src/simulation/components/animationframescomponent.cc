#include "animationframescomponent.h"

namespace mcomm
{

REGISTER_COMPONENT(AnimationFramesComponent);

AnimationFramesComponent::AnimationFramesComponent()
{

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



}
