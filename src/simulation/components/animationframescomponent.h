#pragma once

#include <vector>

#include "media/animationframe.h"
#include "simulation/component.h"


namespace mcomm
{

class AnimationFramesComponent : public Component
{
    DECLARE_COMPONENT(AnimationFramesComponent)

public:
    int frameCount() const;

    void addFrame(const AnimationFrame& frame);

    AnimationFrame frame(int index);

    jsonxx::Object toJson() override;

	void loadJson(const jsonxx::Object& o) override;

private:
    std::vector<AnimationFrame> m_frames;
};

}
