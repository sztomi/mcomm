#pragma once
#include "gtest/gtest.h"

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
