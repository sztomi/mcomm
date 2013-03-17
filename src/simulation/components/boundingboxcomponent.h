#include <SFML/Graphics/Rect.hpp>
#include "simulation/component.h"

namespace mcomm
{

class BoundingBoxComponent : public Component
{
public:
    std::string toString() const;
    void init(const pugi::xml_node &xml);
    sf::IntRect& rect() const;

private:
    sf::IntRect m_rectangle;
};

}
