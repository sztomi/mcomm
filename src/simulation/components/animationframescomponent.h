#pragma once

#include <vector>

#include "media/animationframe.h"
#include "simulation/component.h"

#include <cereal/types/polymorphic.hpp>

namespace mcomm
{

class AnimationFramesComponent : public Component
{
    DECLARE_COMPONENT(AnimationFramesComponent)

public:
    int frameCount() const;

    void addFrame(const AnimationFrame& frame);

    AnimationFrame frame(int index);

private:
    std::vector<AnimationFrame> m_frames;
};

}
