#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "../component.h"

namespace sf
{
    class Texture;
}

class lua_State;


namespace mcomm
{

class SpriteComponent : public Component
{
public:
    SpriteComponent();

    std::string name() const;
    void loadJson(const jsonxx::Object& o);
    jsonxx::Object toJson() const;
    static void luabind(lua_State* L);

    std::shared_ptr<sf::Sprite> sprite() const;

    std::string textureId() const;
    void setTextureId(const std::string& id);
    int spriteCoordX() const;
    void setSpriteCoordX(int value);
    int spriteCoordY() const;
    void setSpriteCoordY(int value);

private:
    void updateTexRectangle();

private:
    std::shared_ptr<sf::Sprite> m_sprite;
    std::shared_ptr<sf::Texture> m_texture;
    std::string m_texture_id;
    int m_sprite_coord_x, m_sprite_coord_y;
};

}
