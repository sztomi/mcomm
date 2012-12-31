#pragma once

#include "simulation/component.h"

namespace mcomm
{

class TextComponent : public Component
{
public:
    std::string toString() const;
    void init(const pugi::xml_node& xml);
    
    std::string text() const;
    void setText(const std::string& value);

private:
    std::string m_text;
};

}
