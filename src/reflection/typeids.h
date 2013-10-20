#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <boost/lexical_cast.hpp>
#include "util/constexpr_crc.h"

namespace mcomm
{

template<class T>
struct TypeID
{
    static const unsigned int value = 0;
};

#define DECLARE_TYPEID(TYPE) template<> struct TypeID<TYPE> { static const unsigned int value = _CRC32(#TYPE); }

DECLARE_TYPEID(int);
DECLARE_TYPEID(double);
DECLARE_TYPEID(float);
DECLARE_TYPEID(bool);
DECLARE_TYPEID(std::string);

#undef DECLARE_TYPEID

#define HANDLE_CASE(TYPE) case _CRC32(#TYPE): return boost::lexical_cast<std::string>(*reinterpret_cast<TYPE*>(p))

template<class R>
std::string asString(void* p, unsigned int type_id)
{
    switch (type_id)
    {
        HANDLE_CASE(int);
        HANDLE_CASE(double);
        HANDLE_CASE(float);
        HANDLE_CASE(bool);
        HANDLE_CASE(std::string);
    }

    return "unknown typeid";
}

#undef HANDLE_CASE

}
