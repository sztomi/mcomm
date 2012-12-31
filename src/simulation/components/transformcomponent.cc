#include "pugixml.hpp"
#include "transformcomponent.h"

namespace mcomm 
{

std::string TransformComponent::toString() const
{
	return "TransformComponent";
}

void TransformComponent::init(const pugi::xml_node& xml)
{
	auto node_scale = xml.child("Scale");
	if (!node_scale.empty())
	{
		float sx = node_scale.child("X").text().as_float();
		float sy = node_scale.child("Y").text().as_float();
		setScale(sx, sy);
	}

	auto node_origin = xml.child("Origin");
	if (!node_origin.empty())
	{
		float sx = node_origin.child("X").text().as_float();
		float sy = node_origin.child("Y").text().as_float();
		setOrigin(sx, sy);
	}

	auto node_position = xml.child("Position");

	if (!node_position.empty())
	{
		float sx = node_position.child("X").text().as_float();
		float sy = node_position.child("Y").text().as_float();
		setPosition(sx, sy);
	}

	// TODO: more properties, more error handling.
}

}