#pragma once

#include "precompiled.h"
#include <memory>

namespace mcomm
{

class World;

/*!
 * This class implements a run-time gui for editing entities.
 */
class Editor
{
public:
    Editor(std::shared_ptr<World>& world);
    void draw();

private:
    void drawEntityList();
    void drawAssetList();
    void drawComponents();

private:
    std::shared_ptr<World> m_world;
    std::unordered_map<std::string, std::function<void()>> m_propeditors;
    int m_selected_entity_idx;
};

}
