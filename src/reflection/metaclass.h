#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <unordered_map>
#include <string>
#include <vector>

#include <boost/format.hpp>

#include "glog/logging.h"
#include "lualite.hpp"
#include "scripting/scriptmanager.h"

namespace mcomm
{

typedef std::unordered_map<std::string, lualite::detail::member_func_type> FuncMap;

class MetaClass
{
public:
    MetaClass(const std::string& name, const FuncMap& functions, const FuncMap& getters, const FuncMap& setters)
        : m_name(name),
          m_functions(functions),
          m_getters(getters),
          m_setters(setters) {}

    template<class C>
    static std::shared_ptr<MetaClass> create(const std::string& name, const lualite::class_<C>& c)
    {
        const auto& funcs = c.functions();
        const auto& getters = c.getters();
        const auto& setters = c.setters();
        return std::make_shared<MetaClass>(name, funcs, getters, setters);
    }

    std::string name() const { return m_name; }

    template<class R, class C>
    R getProperty(C* instance, const std::string& name)
    {
        auto entry = m_getters.find(name);
        if (entry != end(m_getters))
        {
            // unholy black magic follows
            union
            {
                lualite::detail::member_func_type mf;
                R (C::*f)();
            } pfunc;
            
            pfunc.mf = entry->second;
            return ((instance)->*(pfunc.f))();
        }
        return R();
    }

    template<class C>
    std::string getPropertyStr(C* instance, const std::string& name)
    {
        auto script = boost::format(R"SCRIPT(
            o = %1%(instance)
            print o.%2%
            o = nil
            instance = nil
            )SCRIPT") % m_name % name;
        return ScriptManager::instance().doString(instance, script.str());
    }

private:
    std::string m_name;
    FuncMap m_functions;
    FuncMap m_getters;
    FuncMap m_setters;
};

}

