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

    TextComponent t2;
    t2.loadJson(object);

    EXPECT_EQ(t.text(), t2.text());
    EXPECT_EQ(t.size(), t2.size());
    EXPECT_EQ(t.fontFileName(), t2.fontFileName());
}

TEST(TextComponent, lua_access_fields)
{
    using namespace mcomm;

    auto script = R"QUOTE(
            local obj  = TextComponent.new()

            obj.text = "Hello"
            obj.fontFileName = "./res/fonts/zx_spectrum-7.ttf"
            obj.size = 32

            return obj.text
            
            )QUOTE";

    auto& sm = ScriptManager::instance();

    auto ret_val = sm.doString(script);
    EXPECT_EQ(std::string(ret_val), "Hello");

}

TEST(TextComponent, lua_manipulate_cpp_obj)
{
    using namespace mcomm;

    auto& sm = ScriptManager::instance();

    TextComponent t;
    sm.pushInstance(&t, "t");
    sm.doString("t.text = \"luahello\"");

    EXPECT_EQ(t.text(), "luahello");

    t.setText("cpphello");
    auto result = sm.doString("return t.text");

    EXPECT_EQ(result, "cpphello");
}

