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

TEST(TextComponent, lua_binding)
{
    using namespace mcomm;
    
    auto script = R"QUOTE(
            local c = SpriteComponent.new()

            print("1:", c:name())
            print("2:", c.textureId)
            
            )QUOTE";

    auto L = ScriptManager::instance().L();

    luaL_dostring(L, script);
    std::cout << lua_tostring(L, -1) << std::endl;
}

TEST(TextComponent, MetaClass)
{
    using namespace mcomm;
    TextComponent t;
    t.setText("Hello world");
    auto M = t.metaClass();
    LOG(ERROR) << M->getPropertyStr(&t, "text");
}
