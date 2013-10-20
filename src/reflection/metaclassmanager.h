#pragma once

#include <unordered_map>

#include "glog/logging.h"

#include "metaclass.h"

namespace mcomm
{

class MetaClassManager
{
public:
    static MetaClassManager& instance()
    {
        static MetaClassManager inst;
        return inst;
    }

    void registerClass(const std::shared_ptr<MetaClass>& meta_class)
    {
        m_classes.emplace(std::make_pair(meta_class->name(), meta_class));
    }

    std::shared_ptr<MetaClass> getMetaClass(const std::string& name)
    {
        auto pos = m_classes.find(name);

        if (pos != end(m_classes)) 
            return pos->second;

        LOG(ERROR) << "Could not find metaclass for class " << name;
        return std::shared_ptr<MetaClass>();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<MetaClass>> m_classes;
};

}
