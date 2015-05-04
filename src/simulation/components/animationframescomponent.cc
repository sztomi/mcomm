#include "precompiled.h"
#include "animationframescomponent.h"

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
		frames << jsonxx::Object("AnimationFrame", af_meta->jsonSerialize(f));
	}

	result << "frames" << frames;

	return result;
}

void AnimationFramesComponent::loadJson(jsonxx::Object const& o)
{
	auto frames = o.get<jsonxx::Array>("frames");
	auto af_meta = MetaObjectManager::instance().getMetaObject("AnimationFrame");
	m_frames.clear();
	for (std::size_t i = 0; i < frames.size(); ++i)
	{
		auto f = frames.get<jsonxx::Object>(i).get<jsonxx::Object>("AnimationFrame");
		auto frame = ObjectFactory::instance().create<AnimationFrame>("AnimationFrame", f);
		m_frames.push_back(*frame);
	}
}


}
