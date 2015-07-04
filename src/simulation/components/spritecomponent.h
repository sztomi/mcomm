#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace sf
{
    class Texture;
}

namespace mcomm
{

class SpriteComponent : public Component
{
    RTTI()
public:
    SpriteComponent();

    GET std::shared_ptr<sf::Sprite> sprite() const;

    GET std::string textureId() const noexcept;
    SET void setTextureId(const std::string& id);

    GET int spriteCoordX() const noexcept;
    SET void setSpriteCoordX(int value) noexcept;

    GET int spriteCoordY() const noexcept;
    SET void setSpriteCoordY(int value) noexcept;

    HIDDEN void setParent(Entity* parent) override;

    HIDDEN void revive() override;

private:
    void updateTexRectangle();

private:
    std::shared_ptr<sf::Sprite> m_sprite;
    std::shared_ptr<sf::Texture> m_texture;
    std::string m_texture_id;
    int m_sprite_coord_x, m_sprite_coord_y;
};

}
REFLECT_TYPE(mcomm::SpriteComponent)
