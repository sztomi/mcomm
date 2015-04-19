#include <SFML/Graphics/Rect.hpp>
#include "simulation/component.h"

namespace mcomm
{

class BoundingBoxComponent : public Component
{
	DECLARE_COMPONENT(BoundingBoxComponent)

private:
    sf::IntRect m_rectangle;
};

}
