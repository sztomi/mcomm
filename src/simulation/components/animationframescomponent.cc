#include "animationframescomponent.h"
#include "util/bind_meta.h"

namespace mcomm
{

BIND_COMPONENT(AnimationFramesComponent)
	.def("frame_count", &AnimationFramesComponent::frameCount)
BIND_END()

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
