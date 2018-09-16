#pragma once

#include "OSE/TypeDefs.h"
#include "OSE/EnumClassFlags.h"

#include <string>

namespace OSE {

    enum class FileMode
    {
        Read = 0x01,
        Write = 0x02,
        Create = 0x04
    };

    class File
    {
    public:
        virtual ~File() { };

        virtual size_t Read(byte* buffer, size_t length) = 0;
        virtual bool Read(std::string& buffer);

        virtual size_t Write(const byte* buffer, size_t length) = 0;
        virtual bool Write(const std::string& buffer);

        virtual bool Seek(size_t position) = 0;
        virtual bool SeekCurrent(int64 offset) = 0;
        virtual int64 Tell() = 0;
        virtual size_t Length() = 0;
    };
}

ENABLE_BITMASK_OPERATORS(OSE::FileMode);