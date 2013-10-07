#pragma once
#include "gtest/gtest.h"
#include "lua.hpp"

#include "jsonxx.h"
#include "simulation/components/textcomponent.h"

TEST(TextComponent, serialize)
{
    using namespace mcomm;
    using namespace jsonxx;

    TextComponent t;
    t.setText("Hello");
    t.setFontFileName("./res/fonts/zx_spectrum-7.ttf");
    t.setSize(16);

    auto object = t.toJson();
    auto str = object.json();

    TextComponent t2;
    t2.loadJson(object);

    EXPECT_EQ(t.text(), t2.text());
    EXPECT_EQ(t.size(), t2.size());
    EXPECT_EQ(t.fontFileName(), t2.fontFileName());
}

