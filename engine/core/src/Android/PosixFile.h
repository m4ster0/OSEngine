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

        virtual size_t Read(byte* buffer, size_t length) override;

        virtual size_t Write(const byte* buffer, size_t length) override;

        virtual bool Seek(size_t position) override;
        virtual int64 Tell() override;
        virtual size_t Length() override;
    };

}