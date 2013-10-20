#pragma once

#include <lua.hpp>
extern "C" {
#include <lauxlib.h>
}
#include <lualite.hpp>

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

    lua_State* L() const { return m_luaState; }

    template<class C>
    std::string doString(C* instance, std::string script)
    {
        lua_pushlightuserdata(m_luaState, reinterpret_cast<void*>(instance));
        lua_setglobal(m_luaState, "instance");
        luaL_dostring(m_luaState, script.c_str());
        return std::string(lua_tostring(m_luaState, -1));
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
