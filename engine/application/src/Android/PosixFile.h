#pragma once

#include "OSE/System/File.h"

#include <cstdio>

namespace OSE {

    class PosixFileSync: public File
    {
        ::FILE* m_File{ nullptr };

    public:
        PosixFileSync(::FILE* file);
        ~PosixFileSync();

        size_t Read(byte* buffer, size_t length) override;

        size_t Write(const byte* buffer, size_t length) override;

        bool Seek(size_t position) override;
        bool SeekCurrent(int64 offset) override;
        int64 Tell() override;
        size_t Length() override;
    };

}