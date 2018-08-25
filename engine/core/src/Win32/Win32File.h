#pragma once

#include "OSE/System/File.h"
#include "OSE/TypeDefs.h"

#include <Windows.h>

namespace OSE {

    class Win32FileSync : public File
    {
        HANDLE m_File{ INVALID_HANDLE_VALUE }; //file created

    public:
        Win32FileSync(HANDLE file);
        ~Win32FileSync();

        virtual size_t Read(byte* buffer, size_t length) override;

        virtual size_t Write(const byte* buffer, size_t length) override;

        virtual bool Seek(size_t position) override;
        virtual int64 Tell() override;
        virtual size_t Length() override;
    };

}