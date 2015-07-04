#include "SFML/Graphics/Rect.hpp"
#include "glog/logging.h"

#include "media/texturemanager.h"
#include "scripting/scriptmanager.h"
#include "spritecomponent.h"
#include "drawablecomponent.h"

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

std::shared_ptr<sf::Sprite> SpriteComponent::sprite() const noexcept
{
    return m_sprite;
}

std::string SpriteComponent::textureId() const noexcept
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

void SpriteComponent::revive()
{
    setTextureId(m_texture_id);
    updateTexRectangle();
}

int SpriteComponent::spriteCoordX() const noexcept
{
    return m_sprite_coord_x;
}

void SpriteComponent::setSpriteCoordX(int value) noexcept
{
    m_sprite_coord_x = value;
    updateTexRectangle();
}

int SpriteComponent::spriteCoordY() const noexcept
{
    return m_sprite_coord_y;
}

void SpriteComponent::setSpriteCoordY(int value) noexcept
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

void SpriteComponent::setParent(Entity* parent)
{
    auto drawable = parent->COMPONENT(Drawable);
    if (!drawable)
    {
        LOG(ERROR) << "SpriteComponent requires a drawable component in the Entity.";
    }

    drawable->setDrawable(m_sprite);

    Component::setParent(parent);
}

}


