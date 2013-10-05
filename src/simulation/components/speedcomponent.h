#pragma once

#include "simulation/component.h"

class lua_State;

namespace mcomm
{

class SpeedComponent : public Component
{
public:
    SpeedComponent();

    std::string name() const;
    void loadJson(const jsonxx::Object& o);
    jsonxx::Object toJson() const;
    static void luabind(lua_State* L);

    float x() const;
    void setX(float value);
    float y() const;
    void setY(float value);

private:
    float m_x, m_y;
};

}
