#pragma once

#include "precompiled.h"
#include "metaobject.h"

namespace mcomm
{

class MetaObjectManager
{
public:
    typedef void (*BindFunction)();

    static MetaObjectManager& instance()
    {
        static MetaObjectManager inst;
        return inst;
    }

    void registerClass(const std::shared_ptr<MetaObject>& meta_class)
    {
        m_classes.emplace(std::make_pair(meta_class->name(), meta_class));
    }

    void registerBindFunction(BindFunction f)
    {
        m_bind_functions.push_back(f);
    }

    void bindClasses()
    {
        for (auto& bind_function : m_bind_functions)
        {
            bind_function();
        }
    }

    std::shared_ptr<MetaObject> getMetaObject(const std::string& name)
    {
        auto pos = m_classes.find(name);

        if (pos != end(m_classes))
            return pos->second;

        LOG(ERROR) << "Could not find metaObject for class " << name;
        return std::shared_ptr<MetaObject>();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<MetaObject>> m_classes;
    std::vector<BindFunction> m_bind_functions;
};

}
