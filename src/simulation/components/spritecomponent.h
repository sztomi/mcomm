#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "simulation/component.h"

namespace sf
{
    class Texture;
}

namespace mcomm
{

class SpriteComponent : public Component
{
    DECLARE_COMPONENT(SpriteComponent)

public:
    std::shared_ptr<sf::Sprite> sprite() const;

    std::string textureId() const;
    void setTextureId(const std::string& id);

    int spriteCoordX() const;
    void setSpriteCoordX(int value);

    int spriteCoordY() const;
    void setSpriteCoordY(int value);

	void setParent(std::shared_ptr<Entity> const& parent) override;

private:
    void updateTexRectangle();

private:
    std::shared_ptr<sf::Sprite> m_sprite;
    std::shared_ptr<sf::Texture> m_texture;
    std::string m_texture_id;
    int m_sprite_coord_x, m_sprite_coord_y;
};

}
