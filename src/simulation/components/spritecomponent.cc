#include "SFML/Graphics/Rect.hpp"
#include "pugixml.hpp"

#include "spritecomponent.h"
#include "drawablecomponent.h"
#include "media/texturemanager.h"

namespace mcomm
{

SpriteComponent::SpriteComponent()
	: m_sprite(), m_texture(), m_sprite_coord_x(0), m_sprite_coord_y(0)
{
    m_sprite = std::make_shared<sf::Sprite>();
}

std::string SpriteComponent::toString() const
{
	return "SpriteComponent";
}

void SpriteComponent::init(const pugi::xml_node& xml)
{
	setTexture(xml.child("Texture").text().as_string());
	setSpriteCoordX(xml.child("X").text().as_int());
	setSpriteCoordY(xml.child("Y").text().as_int());

    m_parent->COMPONENT(Drawable)->setDrawable(m_sprite);
}

std::shared_ptr<sf::Sprite> SpriteComponent::sprite() const
{
	return m_sprite;
}

void SpriteComponent::setTexture(const std::string& id)
{
	m_texture = TextureManager::instance().texture(id);
	m_sprite->setTexture(*m_texture.get());
}

void SpriteComponent::setSpriteCoordX(int value)
{
	m_sprite_coord_x = value;
	updateTexRectangle();
}

void SpriteComponent::setSpriteCoordY(int value)
{
	m_sprite_coord_y = value;
	updateTexRectangle();
}

void SpriteComponent::updateTexRectangle()
{
	const int sprite_size_x = 32;
	const int sprite_size_y = 32;
	int x = sprite_size_x * m_sprite_coord_x;
	int y = sprite_size_y * m_sprite_coord_y;

	m_sprite->setTextureRect(
		sf::IntRect(x, y, sprite_size_x, sprite_size_y)
	);
}

}
