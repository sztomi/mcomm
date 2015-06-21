#include "precompiled.h"

#include "world.h"
#include "entity.h"
#include "simulation/components/transformcomponent.h"
#include "factories.h"

#include <camp-xml/rapidxml.hpp>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;

namespace mcomm
{

void World::bindClass()
{
    camp::Class::declare<World>()
        .function("update", &World::update)
        .property("entities", &World::m_entities)
        .readable(true)
        .writable(true)
        ;
}

void World::update(float dt)
{
    for (auto& entity : m_entities)
    {
        entity->update(dt);
    }
}

void World::addEntity(Entity* entity)
{
    m_entities.push_back(entity);
}

void World::save(std::string const& fileName)
{
    xml_document<> doc;
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(decl);

    xml_node<>* root = doc.allocate_node(node_element, "world");
    root->append_attribute(doc.allocate_attribute("version", "0.1"));
    doc.append_node(root);

    camp::xml::serialize(camp::UserObject(this), root, "hidden");

    std::fstream out_file(fileName, std::ios::out);
    out_file << doc;
}

void World::load(const std::string& fileName)
{
    auto& meta = camp::classById(campClassId());

    std::ifstream in_file(fileName, std::ios::in);
    xml_document<> doc;
    std::stringstream xml;
    xml << in_file.rdbuf();
    std::string buf = xml.str();
    doc.parse<0>(&buf[0]);
    auto* root = doc.first_node("world");
    camp::xml::deserialize(this, root, "hidden");
}

}
