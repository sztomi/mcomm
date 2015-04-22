#include "animationframescomponent.h"
#include "util/bind_meta.h"
#include "reflection/metaobjectmanager.h"

#include "jsonxx.h"

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


jsonxx::Object AnimationFramesComponent::toJson()
{
	jsonxx::Object result = Component::toJson();
	jsonxx::Array frames;
	auto af_meta = MetaObjectManager::instance().getMetaObject("AnimationFrame");
	for (auto& f : m_frames)
	{
		frames << af_meta->toJson(f);
	}

	result << jsonxx::Object("frames", frames);

	return result;
}



}
