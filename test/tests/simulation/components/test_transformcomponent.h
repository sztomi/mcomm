#pragma once
#include "gtest/gtest.h"

#include "jsonxx.h"
#include "simulation/components/transformcomponent.h"

TEST(TransformComponent, serialize)
{
    using namespace mcomm;
    using namespace jsonxx;

    TransformComponent t;
    t.setScale(3.0f, 4.2f);
    t.setPosition(345.2f, 123.12f);
    t.setOrigin(0.5f, 0.5f);

    auto object = t.toJson();
    auto str = object.json();

    TransformComponent t2;
    Object o; 
    EXPECT_TRUE(o.parse(str));

    t2.loadJson(o);

    EXPECT_FLOAT_EQ(t.getScale().x, t2.getScale().x);
    EXPECT_FLOAT_EQ(t.getScale().y, t2.getScale().y);
    EXPECT_FLOAT_EQ(t.getOrigin().x, t2.getOrigin().x);
    EXPECT_FLOAT_EQ(t.getOrigin().y, t2.getOrigin().y);
    EXPECT_FLOAT_EQ(t.getPosition().x, t2.getPosition().x);
    EXPECT_FLOAT_EQ(t.getPosition().y, t2.getPosition().y);
}
