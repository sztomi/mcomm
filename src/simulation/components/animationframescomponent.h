#pragma once

#include "precompiled.h"
#include "simulation/component.h"
#include "media/animationframe.h"

namespace mcomm
{

class AnimationFramesComponent : public Component
{
    RTTI()
public:
    AnimationFramesComponent();

    GET int frameCount() const noexcept;

    void addFrame(const AnimationFrame& frame);

    AnimationFrame frame(int index);

    static void bindClass();

private:
    std::vector<AnimationFrame> m_frames;
};

}

CAMP_TYPE(mcomm::AnimationFramesComponent)
