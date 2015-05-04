#pragma once

#include "precompiled.h"
#include "scripting/scriptmanager.h"

#define _SWITCH(V) auto VAR = V; if (false) {}

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
          m_setters(setters)
	{
	}

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
		LOG(INFO) << "generic setting " << name << " to " << value;
        if (entry != end(m_setters))
        {
            // unholy black magic follows
            union
            {
                lualite::detail::member_func_type mf;
                void (C::*f)(T);
            } pfunc;

            pfunc.mf = entry->second.func;
            ((instance)->*(pfunc.f))(value);
			return;
        }

        LOG(ERROR) << "Could not find setter for property "
                   << name
                   << ". Read-only property?";
    }
    #undef _CASE

    #define _CASE(TYPE)                                            \
            else if (VAR.hash_code() == TYPE_ID(TYPE).hash_code())                         \
            {                                                      \
				LOG(INFO) << #TYPE;\
                union                                              \
                {                                                  \
                    lualite::detail::member_func_type mf;          \
                    void (C::*f)(TYPE);                            \
                } pfunc;                                           \
                                                                   \
                pfunc.mf = entry->second.func;                     \
				auto real_value = boost::lexical_cast<TYPE>(value);\
				LOG(INFO) << real_value;                           \
                ((instance)->*(pfunc.f))(real_value);              \
            }

    template<class C>
    void setPropertyStr(C* instance, std::string const& name, std::string value)
    {
        auto entry = m_setters.find(name);
		LOG(INFO) << "setting " << name << " to " << value;

        if (entry != end(m_setters))
        {
			LOG(INFO) << name << " " << std::string((*(entry->second.return_type_id)).name(), 4)<< " " << TYPE_ID(int).name();
            _SWITCH(*(entry->second.return_type_id))
                _CASE(int)
                _CASE(unsigned int)
                _CASE(double)
                _CASE(float)
                _CASE(bool)
                else if (entry->second.return_type_id == TYPE_ID(std::string))
				{
					union
					{
						lualite::detail::member_func_type mf;
						void (C::*f)(std::string);
					} pfunc;

					pfunc.mf = entry->second.func;
					((instance)->*(pfunc.f))(value);
					return;
				}
        }

		LOG(ERROR) << "Could not find setter for property "
				   << name
				   << ". Read-only property?";
    }
    #undef _CASE

    #define _CASE(TYPE)                                        \
            else if (VAR == TYPE_ID(TYPE))                     \
            {                                                  \
                union                                          \
                {                                              \
                    lualite::detail::member_func_type mf;      \
                    TYPE (C::*f)();                            \
                } pfunc;                                       \
                                                               \
                pfunc.mf = entry->second.func;                 \
                auto value = ((instance)->*(pfunc.f))();       \
                return boost::lexical_cast<std::string>(value);\
            }

    template<class C>
    std::string getPropertyStr(C* instance, const std::string& name)
    {
        auto entry = m_getters.find(name);
        if (entry != end(m_getters))
        {
            _SWITCH(entry->second.return_type_id)
                _CASE(int)
                _CASE(unsigned int)
                _CASE(double)
                _CASE(float)
                _CASE(bool)
                _CASE(std::string)
        }
		LOG(ERROR) << "error: unknown return type id";
        throw std::runtime_error("error: unknown return type id");
    }
    #undef _CASE

	std::type_index propertyTypeID(const std::string& name)
    {
        auto entry = m_getters.find(name);
        if (entry != end(m_getters))
            return *(entry->second.return_type_id);

		throw std::runtime_error("Unknown property type id ("+name+")");
    }

    std::vector<std::string> propertyNames() const
    {
        std::vector<std::string> result;
        for (auto const& it : m_getters)
            result.push_back(it.first);

        return result;
    }

    #define _CASE(TYPE)                                        \
            else if (VAR == TYPE_ID(TYPE))                     \
            {                                                  \
                union                                          \
                {                                              \
                    lualite::detail::member_func_type mf;      \
                    TYPE (C::*f)();                            \
                } pfunc;                                       \
                                                               \
                pfunc.mf = entry.second.func;                  \
                auto value = ((obj).*(pfunc.f))();			   \
				result << entry.first << value;                \
            }

	template<typename C>
	jsonxx::Object jsonSerialize(C& obj)
	{
		jsonxx::Object result;
		for (auto& entry : m_getters)
		{
			if (entry.first == "name") { continue; }
            _SWITCH(entry.second.return_type_id)
                _CASE(int)
			    _CASE(unsigned int)
			    _CASE(double)
			    _CASE(float)
			    _CASE(bool)
			    _CASE(std::string)
		}
		return result;
	}
    #undef _CASE



private:
    std::string m_name;
    FuncMap m_functions;
    PropFuncMap m_getters;
    PropFuncMap m_setters;
};

}

#undef _SWITCH

