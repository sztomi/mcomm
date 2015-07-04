#include "selectablecomponent.h"

namespace mcomm
{

SelectableComponent::SelectableComponent()
    : m_is_selected(false)
{}

bool SelectableComponent::selected() const noexcept { return m_is_selected; }

void SelectableComponent::setSelected(bool value) noexcept
{
    m_is_selected = value;
}

} /* mcomm */
