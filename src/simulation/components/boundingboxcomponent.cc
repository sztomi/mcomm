#include "pugixml.hpp"
#include "boundingboxcomponent.h"

namespace mcomm
{

std::string BoundingBoxComponent::toString() const
{
    return "BoundingBoxComponent";
}

void BoundingBoxComponent::init(const pugi::xml_node &xml)
{
    m_rectangle.left = xml.child("X").text().as_int();
    m_rectangle.top = xml.child("Y").text().as_int();
    m_rectangle.width = xml.child("Width").text().as_int();
    m_rectangle.height = xml.child("Height").text().as_int();
}

}
