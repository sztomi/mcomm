#pragma once
#include "gtest/gtest.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "jsonxx.h"
#include "simulation/components/spritecomponent.h"

#include <iostream>

TEST(SpriteComponent, serialize)
{
    using namespace mcomm;
    using namespace jsonxx;

    SpriteComponent s;
    s.setTextureId("sprite1");
    s.setSpriteCoordX(0);
    s.setSpriteCoordY(3);
    
    auto object = s.toJson();
    auto str = object.json();

    SpriteComponent s2;
    s2.loadJson(object);

    EXPECT_EQ(s.textureId(), s2.textureId());
    EXPECT_EQ(s.spriteCoordX(), s2.spriteCoordX());
    EXPECT_EQ(s.spriteCoordY(), s2.spriteCoordY());
}

TEST(SpriteComponent, lua_binding)
{
    using namespace mcomm;
    auto L = luaL_newstate();
    luaL_openlibs(L);

    SpriteComponent::luabind(L);
    
    auto script = R"QUOTE(
            local c = SpriteComponent.new()

            print("1:", c:name())
            print("2:", c.textureId)
            
            )QUOTE";

    luaL_dostring(L, script);
    std::cout << lua_tostring(L, -1) << std::endl;
}
