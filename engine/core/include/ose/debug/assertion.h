#pragma once

#include "ose/typedef.h"
#include "ose/debug/file_info.h"

#include <fmt/format.h>

namespace ose::debug {

    //Assertion is meant to be used only as temp object
    class Assertion
    {
        const FileInfo& m_info;
        const char* m_format;
    public:
        inline Assertion(const FileInfo& info, const char* format): m_info{ info }, m_format{ format } { }
        inline ~Assertion() = default;

        template<typename... FormatArgs>
        void raise(FormatArgs&&... formatArgs)
        {
            fmt::format(m_format, std::forward<FormatArgs>(formatArgs)...);
        }
    };

}