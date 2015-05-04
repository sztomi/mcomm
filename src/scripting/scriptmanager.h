#pragma once

#include "precompiled.h"

namespace mcomm
{

class ScriptManager
{
public:
    static ScriptManager& instance()
    {
        static ScriptManager inst;
        return inst;
    }

    ScriptManager(const ScriptManager&) = delete;

    lua_State* L() const { return m_luaState; }

    std::string doString(const std::string& script)
    {
        luaL_dostring(m_luaState, script.c_str());
        auto ret = lua_tostring(m_luaState, -1);
        if (ret)
            return std::string(ret);
        else
            return "";
    }

    template<class C>
    void pushInstance(C* instance, const std::string& name)
    {
        lualite::detail::push_instance(m_luaState, instance, name);
    }

    template<class C>
    void registerClass(lualite::class_<C>& c)
    {
        lualite::module(m_luaState, c);
    }

    ~ScriptManager()
    {
        lua_close(m_luaState);
    }

private:
    ScriptManager()
    {
        m_luaState = luaL_newstate();
        luaL_openlibs(m_luaState);
    }


private:
    lua_State* m_luaState;
};

}
