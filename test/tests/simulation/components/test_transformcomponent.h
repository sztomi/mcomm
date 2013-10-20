#pragma once
#include "gtest/gtest.h"

#include "simulation/components/transformcomponent.h"

TEST(TransformComponent, serialize)
{
    using namespace mcomm;

    TransformComponent t;
    t.setScale(3.0f, 4.2f);
    t.setPosition(345.2f, 123.12f);
    t.setOrigin(0.5f, 0.5f);

    auto object = t.toJson();
    auto str = object.json();
    LOG(ERROR) << str;

    TransformComponent t2;

    t2.loadJson(object);

    EXPECT_FLOAT_EQ(t.scaleX(), t2.scaleX());
    EXPECT_FLOAT_EQ(t.scaleY(), t2.scaleY());
    EXPECT_FLOAT_EQ(t.originX(), t2.originX());
    EXPECT_FLOAT_EQ(t.originY(), t2.originY());
    EXPECT_FLOAT_EQ(t.positionX(), t2.positionX());
    EXPECT_FLOAT_EQ(t.positionY(), t2.positionY());
}
