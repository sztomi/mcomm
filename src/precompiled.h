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
#include <Python.h>
#include <boost/python.hpp>
#include <boost/lexical_cast.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <camp/camptype.hpp>
#include <camp/class.hpp>
#include <camp/classbuilder.hpp>
#include <camp/classget.hpp>

#include "Box2D/Box2D.h"
#include "glog/logging.h"

// ----------------------------------------

#define TYPE_ID(TYPE) std::type_index(typeid(TYPE))

#include "macros.h"

#include "util/bind_meta.h"
#include "util/constexpr_crc.h"

#include "simulation/component.h"
#include "simulation/system.h"

#include "scripting/scriptmanager.h"

#include "simulation/entity.h"
