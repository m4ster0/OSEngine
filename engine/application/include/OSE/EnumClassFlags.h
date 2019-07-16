#pragma once

#include <type_traits>

#define ENABLE_BITMASK_OPERATORS(x) \
    template<> struct BitMaskOperators<x> { static const bool enabled = true; }

template<typename Enum>
struct BitMaskOperators
{
    static const bool enabled = false;
};

template<typename Enum>
constexpr typename std::enable_if<BitMaskOperators<Enum>::enabled, Enum>::type
operator|(Enum lhs, Enum rhs)
{
    //static_assert(std::is_enum<Enum>::value);

    using type = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (static_cast<type>(lhs) | static_cast<type>(rhs));
}

template<typename Enum>
constexpr typename std::enable_if<BitMaskOperators<Enum>::enabled, Enum>::type
operator&(Enum lhs, Enum rhs)
{
    //static_assert(std::is_enum<Enum>::value);

    using type = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (static_cast<type>(lhs) & static_cast<type>(rhs));
}

template<typename Enum>
constexpr typename std::enable_if<BitMaskOperators<Enum>::enabled, Enum>::type
operator~(Enum rhs)
{
    //static_assert(std::is_enum<Enum>::value);

    using type = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (~static_cast<type>(rhs));
}

template<typename Enum>
constexpr typename std::enable_if<BitMaskOperators<Enum>::enabled, Enum>::type&
operator|=(Enum& lhs, Enum rhs)
{
    //static_assert(std::is_enum<Enum>::value);

    using type = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum> (static_cast<type>(lhs) | static_cast<type>(rhs));
    return lhs;
}

template<typename Enum>
constexpr typename std::enable_if<BitMaskOperators<Enum>::enabled, Enum>::type&
operator&=(Enum& lhs, Enum rhs)
{
    //static_assert(std::is_enum<Enum>::value);

    using type = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum> (static_cast<type>(lhs) & static_cast<type>(rhs));
    return lhs;
}