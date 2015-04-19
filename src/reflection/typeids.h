#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <boost/lexical_cast.hpp>
#include "util/constexpr_crc.h"

namespace mcomm
{

#define TYPE_ID(TYPE) _CRC32(#TYPE)

template<class T>
struct TypeID
{
    static const unsigned int value = 0;
};

#define DECLARE_TYPEID(TYPE) template<> struct TypeID<TYPE> { static const unsigned int value = TYPE_ID(TYPE); }

DECLARE_TYPEID(int);
DECLARE_TYPEID(unsigned int);
DECLARE_TYPEID(double);
DECLARE_TYPEID(float);
DECLARE_TYPEID(bool);
DECLARE_TYPEID(std::string);

#undef DECLARE_TYPEID

}
