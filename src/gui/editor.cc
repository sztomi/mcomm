#include "precompiled.h"
#include "editor.h"
#include "simulation/world.h"

using namespace ImGui;

const int INVALID_IDX = -1;

namespace mcomm
{

Editor::Editor(std::shared_ptr<World>& world)
    : m_world(world),
      m_selected_entity_idx(INVALID_IDX)
{
}

void Editor::draw()
{
    using namespace ImGui;
    auto& io = GetIO();

    static bool ui = true;

    if(Begin("World", &ui, ImVec2(100, 100)))
    {
        drawEntityList();
        drawAssetList();
    }

    //ShowTestWindow();

    if (m_selected_entity_idx != INVALID_IDX)
    {
        drawComponents();
    }

    End();
    Render();
}

void Editor::drawEntityList()
{
    if (CollapsingHeader("Entities"))
    {
        //BeginChild("Items");

        for (std::size_t i = 0; i < m_world->m_entities.size(); ++i)
        {
            auto e = m_world->m_entities[i];
            if (Selectable(e->name().c_str(), m_selected_entity_idx == i))
            {
                m_selected_entity_idx = i;
            }
        }

        //EndChild();
    }
}

void Editor::drawAssetList()
{
    if (CollapsingHeader("Assets"))
    {
    }
}

void Editor::drawComponents()
{
    if (m_selected_entity_idx == INVALID_IDX) { return; }

    Begin("Components");
    auto entity = m_world->m_entities[m_selected_entity_idx];

    for (auto c : entity->m_all_components)
    {
        auto& metaClass = camp::classById(c->campClassId());
        CollapsingHeader(metaClass.name());
    }

    End();
}


} /* mcomm */
