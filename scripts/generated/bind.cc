

#include <boost/python.hpp>
#include <camp/camptype.hpp>
#include <camp/class.hpp>

#include "transformcomponent.h"
#include "boundingboxcomponent.h"
#include "textcomponent.h"
#include "fontcomponent.h"
#include "spriteanimationsystem.h"
#include "factories.h"
#include "b2dcomponent.h"
#include "keyboardinputsystem.h"
#include "entity.h"
#include "speedcomponent.h"
#include "component.h"
#include "animationframescomponent.h"
#include "spritecomponent.h"
#include "velocitysystem.h"
#include "rendersystem.h"
#include "textrendersystem.h"
#include "world.h"
#include "drawablecomponent.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(mcomm)
{
    // ../src/simulation/component.h
    class_<mcomm::Component>("mcomm::Component")
        .def("set_parent", &mcomm::Component::setParent)
        .def("name", &mcomm::Component::name)
        .def("load_json", &mcomm::Component::loadJson)
        .def("to_json", &mcomm::Component::toJson)
        .def("meta_object", &mcomm::Component::metaObject)
    ;

    // ../src/simulation/component.h
    class_<mcomm::System, bases<mcomm::Component>>("mcomm::System")
        .def("update", &mcomm::System::update)
    ;

    // ../src/simulation/entity.h
    class_<mcomm::Entity, bases<std::enable_shared_from_this<Entity>>>("mcomm::Entity")
        .def("attach_component", &mcomm::Entity::attachComponent)
        .def("attach_system", &mcomm::Entity::attachSystem)
        .def("id", &mcomm::Entity::id)
        .def("to_string", &mcomm::Entity::toString)
        .def("name", &mcomm::Entity::name)
        .def("update", &mcomm::Entity::update)
        .def("to_json", &mcomm::Entity::toJson)
    ;

    // ../src/simulation/factories.h
    class_<mcomm::ObjectFactory>("mcomm::ObjectFactory")
        .def("instance", &mcomm::ObjectFactory::instance)
        .def("register_class", &mcomm::ObjectFactory::registerClass)
    ;

    // ../src/simulation/factories.h
    class_<mcomm::EntityFactory>("mcomm::EntityFactory")
        .def("instance", &mcomm::EntityFactory::instance)
        .def("create_new", &mcomm::EntityFactory::createNew)
        .def("create_new", &mcomm::EntityFactory::createNew)
    ;

    // ../src/simulation/world.h
    class_<mcomm::World>("mcomm::World")
        .def("update", &mcomm::World::update)
        .def("add_entity", &mcomm::World::addEntity)
        .def("load_json", &mcomm::World::loadJson)
        .def("save_json", &mcomm::World::saveJson)
    ;

    // ../src/simulation/components/animationframescomponent.h
    class_<mcomm::AnimationFramesComponent, bases<mcomm::Component>>("mcomm::AnimationFramesComponent")
        .def("add_frame", &mcomm::AnimationFramesComponent::addFrame)
        .def("frame", &mcomm::AnimationFramesComponent::frame)
        .property("frame_count", &mcomm::AnimationFramesComponent::frameCount)
    ;

    // ../src/simulation/components/drawablecomponent.h
    class_<mcomm::DrawableComponent, bases<mcomm::Component>>("mcomm::DrawableComponent")
        .def("set_drawable", &mcomm::DrawableComponent::setDrawable)
        .def("drawable", &mcomm::DrawableComponent::drawable)
    ;

    // ../src/simulation/components/speedcomponent.h
    class_<mcomm::SpeedComponent, bases<mcomm::Component>>("mcomm::SpeedComponent")
        .property("y", &mcomm::SpeedComponent::y, &mcomm::SpeedComponent::setY)
        .property("x", &mcomm::SpeedComponent::x, &mcomm::SpeedComponent::setX)
    ;

    // ../src/simulation/components/textcomponent.h
    class_<mcomm::TextComponent, bases<mcomm::Component>>("mcomm::TextComponent")
        .property("text", &mcomm::TextComponent::text, &mcomm::TextComponent::setText)
        .property("font_file_name", &mcomm::TextComponent::fontFileName, &mcomm::TextComponent::setFontFileName)
        .property("size", &mcomm::TextComponent::size, &mcomm::TextComponent::setSize)
    ;

    // ../src/simulation/components/fontcomponent.h
    class_<mcomm::FontComponent, bases<mcomm::Component>>("mcomm::FontComponent")
        .def("font", &mcomm::FontComponent::font)
        .property("file_name", &mcomm::FontComponent::fileName, &mcomm::FontComponent::setFileName)
        .property("size", &mcomm::FontComponent::size, &mcomm::FontComponent::setSize)
    ;

    // ../src/simulation/components/spritecomponent.h
    class_<mcomm::SpriteComponent, bases<mcomm::Component>>("mcomm::SpriteComponent")
        .property("texture_id", &mcomm::SpriteComponent::textureId, &mcomm::SpriteComponent::setTextureId)
        .property("sprite", &mcomm::SpriteComponent::sprite)
        .property("sprite_coord_x", &mcomm::SpriteComponent::spriteCoordX, &mcomm::SpriteComponent::setSpriteCoordX)
        .property("sprite_coord_y", &mcomm::SpriteComponent::spriteCoordY, &mcomm::SpriteComponent::setSpriteCoordY)
    ;

    // ../src/simulation/components/transformcomponent.h
    class_<mcomm::TransformComponent, bases<mcomm::Component,sf::Transformable>>("mcomm::TransformComponent")
        .property("position_x", &mcomm::TransformComponent::positionX, &mcomm::TransformComponent::setPositionX)
        .property("position_y", &mcomm::TransformComponent::positionY, &mcomm::TransformComponent::setPositionY)
        .property("scale_x", &mcomm::TransformComponent::scaleX, &mcomm::TransformComponent::setScaleX)
        .property("origin_y", &mcomm::TransformComponent::originY, &mcomm::TransformComponent::setOriginY)
        .property("scale_y", &mcomm::TransformComponent::scaleY, &mcomm::TransformComponent::setScaleY)
        .property("origin_x", &mcomm::TransformComponent::originX, &mcomm::TransformComponent::setOriginX)
    ;

    // ../src/simulation/systems/spriteanimationsystem.h
    class_<mcomm::SpriteAnimationSystem, bases<mcomm::System>>("mcomm::SpriteAnimationSystem")
        .def("update", &mcomm::SpriteAnimationSystem::update)
        .def("stop_at", &mcomm::SpriteAnimationSystem::stopAt)
        .def("start_from", &mcomm::SpriteAnimationSystem::startFrom)
        .property("is_running", &mcomm::SpriteAnimationSystem::isRunning)
    ;

    // ../src/simulation/systems/textrendersystem.h
    class_<mcomm::TextRenderSystem, bases<mcomm::System>>("mcomm::TextRenderSystem")
        .def("update", &mcomm::TextRenderSystem::update)
    ;

    // ../src/simulation/systems/velocitysystem.h
    class_<mcomm::VelocitySystem, bases<mcomm::System>>("mcomm::VelocitySystem")
        .def("update", &mcomm::VelocitySystem::update)
        .property("y", &mcomm::VelocitySystem::y, &mcomm::VelocitySystem::setY)
        .property("x", &mcomm::VelocitySystem::x, &mcomm::VelocitySystem::setX)
    ;

    // ../src/simulation/systems/keyboardinputsystem.h
    class_<mcomm::KeyboardInputSystem, bases<mcomm::System>>("mcomm::KeyboardInputSystem")
        .def("update", &mcomm::KeyboardInputSystem::update)
    ;

    // ../src/simulation/systems/rendersystem.h
    class_<mcomm::RenderSystem, bases<mcomm::System>>("mcomm::RenderSystem")
        .def("update", &mcomm::RenderSystem::update)
    ;

}

void init_camp_bindings()
{
    // ../src/simulation/component.h
    camp::Class::declare<mcomm::Component>("mcomm::Component")
        .function("setParent", &mcomm::Component::setParent)
        .function("name", &mcomm::Component::name)
        .function("loadJson", &mcomm::Component::loadJson)
        .function("toJson", &mcomm::Component::toJson)
        .function("metaObject", &mcomm::Component::metaObject)
    ;

    // ../src/simulation/component.h
    camp::Class::declare<mcomm::System>("mcomm::System")
        .function("update", &mcomm::System::update)
    ;

    // ../src/simulation/entity.h
    camp::Class::declare<mcomm::Entity>("mcomm::Entity")
        .function("attachComponent", &mcomm::Entity::attachComponent)
        .function("attachSystem", &mcomm::Entity::attachSystem)
        .function("id", &mcomm::Entity::id)
        .function("toString", &mcomm::Entity::toString)
        .function("name", &mcomm::Entity::name)
        .function("update", &mcomm::Entity::update)
        .function("toJson", &mcomm::Entity::toJson)
    ;

    // ../src/simulation/factories.h
    camp::Class::declare<mcomm::ObjectFactory>("mcomm::ObjectFactory")
        .function("instance", &mcomm::ObjectFactory::instance)
        .function("registerClass", &mcomm::ObjectFactory::registerClass)
    ;

    // ../src/simulation/factories.h
    camp::Class::declare<mcomm::EntityFactory>("mcomm::EntityFactory")
        .function("instance", &mcomm::EntityFactory::instance)
        .function("createNew", &mcomm::EntityFactory::createNew)
        .function("createNew", &mcomm::EntityFactory::createNew)
    ;

    // ../src/simulation/world.h
    camp::Class::declare<mcomm::World>("mcomm::World")
        .function("update", &mcomm::World::update)
        .function("addEntity", &mcomm::World::addEntity)
        .function("loadJson", &mcomm::World::loadJson)
        .function("saveJson", &mcomm::World::saveJson)
    ;

    // ../src/simulation/components/animationframescomponent.h
    camp::Class::declare<mcomm::AnimationFramesComponent>("mcomm::AnimationFramesComponent")
        .function("addFrame", &mcomm::AnimationFramesComponent::addFrame)
        .function("frame", &mcomm::AnimationFramesComponent::frame)
        .property("frameCount", &mcomm::AnimationFramesComponent::frameCount)
    ;

    // ../src/simulation/components/drawablecomponent.h
    camp::Class::declare<mcomm::DrawableComponent>("mcomm::DrawableComponent")
        .function("setDrawable", &mcomm::DrawableComponent::setDrawable)
        .function("drawable", &mcomm::DrawableComponent::drawable)
    ;

    // ../src/simulation/components/speedcomponent.h
    camp::Class::declare<mcomm::SpeedComponent>("mcomm::SpeedComponent")
        .property("y", &mcomm::SpeedComponent::y, &mcomm::SpeedComponent::setY)
        .property("x", &mcomm::SpeedComponent::x, &mcomm::SpeedComponent::setX)
    ;

    // ../src/simulation/components/textcomponent.h
    camp::Class::declare<mcomm::TextComponent>("mcomm::TextComponent")
        .property("text", &mcomm::TextComponent::text, &mcomm::TextComponent::setText)
        .property("fontFileName", &mcomm::TextComponent::fontFileName, &mcomm::TextComponent::setFontFileName)
        .property("size", &mcomm::TextComponent::size, &mcomm::TextComponent::setSize)
    ;

    // ../src/simulation/components/fontcomponent.h
    camp::Class::declare<mcomm::FontComponent>("mcomm::FontComponent")
        .function("font", &mcomm::FontComponent::font)
        .property("fileName", &mcomm::FontComponent::fileName, &mcomm::FontComponent::setFileName)
        .property("size", &mcomm::FontComponent::size, &mcomm::FontComponent::setSize)
    ;

    // ../src/simulation/components/spritecomponent.h
    camp::Class::declare<mcomm::SpriteComponent>("mcomm::SpriteComponent")
        .property("textureId", &mcomm::SpriteComponent::textureId, &mcomm::SpriteComponent::setTextureId)
        .property("sprite", &mcomm::SpriteComponent::sprite)
        .property("spriteCoordX", &mcomm::SpriteComponent::spriteCoordX, &mcomm::SpriteComponent::setSpriteCoordX)
        .property("spriteCoordY", &mcomm::SpriteComponent::spriteCoordY, &mcomm::SpriteComponent::setSpriteCoordY)
    ;

    // ../src/simulation/components/transformcomponent.h
    camp::Class::declare<mcomm::TransformComponent>("mcomm::TransformComponent")
        .property("positionX", &mcomm::TransformComponent::positionX, &mcomm::TransformComponent::setPositionX)
        .property("positionY", &mcomm::TransformComponent::positionY, &mcomm::TransformComponent::setPositionY)
        .property("scaleX", &mcomm::TransformComponent::scaleX, &mcomm::TransformComponent::setScaleX)
        .property("originY", &mcomm::TransformComponent::originY, &mcomm::TransformComponent::setOriginY)
        .property("scaleY", &mcomm::TransformComponent::scaleY, &mcomm::TransformComponent::setScaleY)
        .property("originX", &mcomm::TransformComponent::originX, &mcomm::TransformComponent::setOriginX)
    ;

    // ../src/simulation/systems/spriteanimationsystem.h
    camp::Class::declare<mcomm::SpriteAnimationSystem>("mcomm::SpriteAnimationSystem")
        .function("update", &mcomm::SpriteAnimationSystem::update)
        .function("stopAt", &mcomm::SpriteAnimationSystem::stopAt)
        .function("startFrom", &mcomm::SpriteAnimationSystem::startFrom)
        .property("isRunning", &mcomm::SpriteAnimationSystem::isRunning)
    ;

    // ../src/simulation/systems/textrendersystem.h
    camp::Class::declare<mcomm::TextRenderSystem>("mcomm::TextRenderSystem")
        .function("update", &mcomm::TextRenderSystem::update)
    ;

    // ../src/simulation/systems/velocitysystem.h
    camp::Class::declare<mcomm::VelocitySystem>("mcomm::VelocitySystem")
        .function("update", &mcomm::VelocitySystem::update)
        .property("y", &mcomm::VelocitySystem::y, &mcomm::VelocitySystem::setY)
        .property("x", &mcomm::VelocitySystem::x, &mcomm::VelocitySystem::setX)
    ;

    // ../src/simulation/systems/keyboardinputsystem.h
    camp::Class::declare<mcomm::KeyboardInputSystem>("mcomm::KeyboardInputSystem")
        .function("update", &mcomm::KeyboardInputSystem::update)
    ;

    // ../src/simulation/systems/rendersystem.h
    camp::Class::declare<mcomm::RenderSystem>("mcomm::RenderSystem")
        .function("update", &mcomm::RenderSystem::update)
    ;

}

namespace mcomm
{

void bindClasses()
{
    Py_Initialize();
    initmcomm();
    init_camp_bindings();
}

}
