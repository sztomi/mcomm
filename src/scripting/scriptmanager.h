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

    template<class C>
    void pushInstance(C* instance, const std::string& name)
    {
        namespace bp = boost::python;
        bp::import("__main__").attr(name.c_str()) = bp::object(bp::ptr(instance));
    }

    void execString(const std::string& script)
    {
        namespace bp = boost::python;
        auto main_module = bp::import("__main__");
        auto main_ns = main_module.attr("__dict__");
        bp::exec(bp::str(script), main_ns);
    }

    ~ScriptManager()
    {
        Py_Finalize();
    }

private:
    ScriptManager()
    {
        Py_Initialize();
    }
};

}
