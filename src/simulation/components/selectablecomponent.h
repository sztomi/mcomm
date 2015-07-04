#pragma once

#include "simulation/component.h"

namespace mcomm
{

/*!
 * \brief Allows selection for design-time.
 */
class SelectableComponent : public Component
{
    RTTI()
public:
    SelectableComponent();

    GET bool selected() const noexcept;
    SET void setSelected(bool value) noexcept;

private:
    bool m_is_selected;
};

}

REFLECT_TYPE(mcomm::SelectableComponent)
