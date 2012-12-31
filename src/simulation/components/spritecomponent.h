#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "../component.h"

namespace sf
{
	class Texture;
}

namespace mcomm
{

class SpriteComponent : public Component
{
public:
	SpriteComponent();

	void init(const pugi::xml_node& xml);
	std::string toString() const;
	sf::Sprite sprite() const;

	void setTexture(const std::string& id);
	void setSpriteCoordX(int value);
	void setSpriteCoordY(int value);

private:
	void updateTexRectangle();

private:
	sf::Sprite m_sprite;
	std::shared_ptr<sf::Texture> m_texture;
	int m_sprite_coord_x, m_sprite_coord_y;
};

}