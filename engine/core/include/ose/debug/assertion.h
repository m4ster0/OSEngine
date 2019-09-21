#pragma once

#include "ose/typedef.h"
#include "ose/debug/file_info.h"

#include <fmt/format.h>

namespace ose::debug {

    //Assertion is meant to be used only as temp object
    class Assertion
    {
        const FileInfo& m_info;
        const char* m_conditionMessage;
    public:
        inline Assertion(const FileInfo& info, const char* conditionMessage):
            m_info{ info }, m_conditionMessage{ conditionMessage } { }
        inline ~Assertion() = default;

        template<typename... FormatArgs>
        void raise(const char* format, FormatArgs&&... formatArgs)
        {
            fmt::format("======== ASSERT =========");
            fmt::format(m_conditionMessage);
            fmt::format("{}:{}", m_info.c_file, m_info.c_line);
            fmt::format(format, std::forward<FormatArgs>(formatArgs)...);
        }
    };

}
