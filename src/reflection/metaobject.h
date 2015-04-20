#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <unordered_map>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "glog/logging.h"
#include "lualite.hpp"
#include "scripting/scriptmanager.h"

namespace mcomm
{

typedef std::unordered_map<std::string, lualite::detail::map_member_info_type> PropFuncMap;
typedef std::unordered_map<std::string, lualite::detail::member_info_type> FuncMap;

class MetaObject
{
public:
    MetaObject(const std::string& name, const FuncMap& functions, const PropFuncMap& getters, const PropFuncMap& setters)
        : m_name(name),
          m_functions(functions),
          m_getters(getters),
          m_setters(setters) {}

    template<class C>
    static std::shared_ptr<MetaObject> create(const std::string& name, const lualite::class_<C>& c)
    {
        const auto& funcs = c.functions();
        const auto& getters = c.getters();
        const auto& setters = c.setters();
        return std::make_shared<MetaObject>(name, funcs, getters, setters);
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

            pfunc.mf = entry->second.func;
            return ((instance)->*(pfunc.f))();
        }
        return R();
    }

    template<class C, class T>
    void setProperty(C* instance, const std::string& name, T value)
    {
        auto entry = m_setters.find(name);
        if (entry != end(m_setters))
        {
            // unholy black magic follows
            union
            {
                lualite::detail::member_func_type mf;
                void (C::*f)(T);
            } pfunc;

            pfunc.mf = entry->second.func;
            return ((instance)->*(pfunc.f))(value);
        }

        LOG(ERROR) << "Could not find setter for property "
                   << name
                   << ". Read-only property?";
    }

    #define HANDLE_CASE(TYPE)                                  \
            case _CRC32(#TYPE):                                \
            {                                                  \
                union                                          \
                {                                              \
                    lualite::detail::member_func_type mf;      \
                    TYPE (C::*f)();                            \
                } pfunc;                                       \
                                                               \
                pfunc.mf = entry->second.func;                      \
                auto value = ((instance)->*(pfunc.f))();       \
                return boost::lexical_cast<std::string>(value);\
            }                                                  \
            break;

    template<class C>
    std::string getPropertyStr(C* instance, const std::string& name)
    {
        auto entry = m_getters.find(name);
        if (entry != end(m_getters))
        {
            switch (entry->second.return_type_id)
            {
            HANDLE_CASE(int)
            HANDLE_CASE(unsigned int)
            HANDLE_CASE(double)
            HANDLE_CASE(float)
            HANDLE_CASE(bool)
            HANDLE_CASE(std::string)
            }
        }
        return "error: unknown return type id";
    }
    #undef HANDLE_CASE

    unsigned int propertyTypeID(const std::string& name)
    {
        auto entry = m_getters.find(name);
        if (entry != end(m_getters))
            return entry->second.return_type_id;

        return 0;
    }

    std::vector<std::string> propertyNames() const
    {
        std::vector<std::string> result;
        for (auto const& it : m_getters)
            result.push_back(it.first);

        return result;
    }



private:
    std::string m_name;
    FuncMap m_functions;
    PropFuncMap m_getters;
    PropFuncMap m_setters;
};

}

