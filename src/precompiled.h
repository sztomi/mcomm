#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <functional>
#include <sstream>
#include <typeindex>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "SFML/Graphics/Transformable.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "lua.hpp"
extern "C"
{
#include "lauxlib.h"
}

#include "Box2D/Box2D.h"
#include "glog/logging.h"

#include "lualite.hpp"
#include "jsonxx.h"

// ----------------------------------------

#define TYPE_ID(TYPE) std::type_index(typeid(TYPE))

#include "util/bind_meta.h"
#include "util/constexpr_crc.h"

#include "simulation/component.h"
#include "simulation/system.h"

#include "scripting/scriptmanager.h"

#include "simulation/entity.h"
