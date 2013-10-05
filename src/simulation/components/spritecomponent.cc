#include "SFML/Graphics/Rect.hpp"
#include "jsonxx.h"

#include "drawablecomponent.h"
#include "media/texturemanager.h"
#include "spritecomponent.h"

using namespace jsonxx;

namespace mcomm
{

SpriteComponent::SpriteComponent()
    : m_sprite(), 
      m_texture(),
      m_sprite_coord_x(0),
      m_sprite_coord_y(0)
{
    m_sprite = std::make_shared<sf::Sprite>();
}

std::string SpriteComponent::name() const
{
    return "SpriteComponent";
}

void SpriteComponent::loadJson(const Object& o)
{
    setTextureId(o.get<String>("texture_id"));
    setSpriteCoordX(static_cast<int>(o.get<Number>("x")));
    setSpriteCoordY(static_cast<int>(o.get<Number>("y")));

    //m_parent->COMPONENT(Drawable)->setDrawable(m_sprite);
}

Object SpriteComponent::toJson() const
{
    Object result;

    result << "texture_id" << m_texture_id;
    result << "x" << m_sprite_coord_x;
    result << "y" << m_sprite_coord_y;

    return result;
}

std::shared_ptr<sf::Sprite> SpriteComponent::sprite() const
{
    return m_sprite;
}

std::string SpriteComponent::textureId() const
{
    return m_texture_id;
}

void SpriteComponent::setTextureId(const std::string& id)
{
    m_texture_id = id;

    m_texture = TextureManager::instance().texture(id);
    DLOG_IF(ERROR, m_texture.get() == nullptr)
        << "Could not find texture by id "
        << id;

    if (m_texture.get() != nullptr)
        m_sprite->setTexture(*m_texture.get());
}

int SpriteComponent::spriteCoordX() const 
{
    return m_sprite_coord_x;
}

void SpriteComponent::setSpriteCoordX(int value)
{
    m_sprite_coord_x = value;
    updateTexRectangle();
}

int SpriteComponent::spriteCoordY() const
{
    return m_sprite_coord_y;
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
