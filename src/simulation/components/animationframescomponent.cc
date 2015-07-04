#include "precompiled.h"
#include "animationframescomponent.h"

namespace mcomm
{

AnimationFramesComponent::AnimationFramesComponent()
{

}

int AnimationFramesComponent::frameCount() const noexcept
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

void AnimationFramesComponent::bindClass()
{
    camp::Class::declare<AnimationFramesComponent>()
        .base<mcomm::Component>()
        .constructor0()
        .function("addFrame", &AnimationFramesComponent::addFrame)
        .function("frame", &AnimationFramesComponent::frame)
        .property("frames", &AnimationFramesComponent::m_frames)
    ;
}

}
