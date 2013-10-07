#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>

#include "simulation/component.h"

class lua_State;

namespace mcomm
{

class DrawableComponent : public Component
{
public:
    DrawableComponent();

    std::string name() const;
    void loadJson(const jsonxx::Object& o);
    jsonxx::Object toJson() const;
    static void luabind(lua_State* L);

    void setDrawable(const std::shared_ptr<sf::Drawable> &value);
    std::shared_ptr<sf::Drawable> drawable() const;

private:
    std::shared_ptr<sf::Drawable> m_drawable;
    std::string m_kind;
};

}
