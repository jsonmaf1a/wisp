#pragma once

#include <string_view>

namespace StringUtils
{
    template <typename T> constexpr std::string_view toString(T);
    template <typename T> constexpr char toChar(T);
} // namespace StringUtils
