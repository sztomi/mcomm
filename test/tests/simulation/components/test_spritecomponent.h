#pragma once
#include "gtest/gtest.h"

#include "simulation/components/spritecomponent.h"
#include "scripting/scriptmanager.h"

#include <iostream>

TEST(SpriteComponent, serialize)
{
    using namespace mcomm;

    SpriteComponent s;
    s.setTextureId("sprite1");
    s.setSpriteCoordX(0);
    s.setSpriteCoordY(3);
    
    auto object = s.toJson();

    SpriteComponent s2;
    s2.loadJson(object);

    EXPECT_EQ(s.textureId(), s2.textureId());
    EXPECT_EQ(s.spriteCoordX(), s2.spriteCoordX());
    EXPECT_EQ(s.spriteCoordY(), s2.spriteCoordY());
}

TEST(SpriteComponent, lua_binding)
{
    using namespace mcomm;
    auto& sm = ScriptManager::instance();

    auto script = R"QUOTE(
            local c = SpriteComponent.new()

            print("1:", c:name())
            print("2:", c.textureId)
            
            )QUOTE";

    sm.doString(script);
}
