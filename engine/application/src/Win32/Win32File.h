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

        size_t Read(byte* buffer, size_t length) override;

        size_t Write(const byte* buffer, size_t length) override;

        bool Seek(size_t position) override;
        bool SeekCurrent(int64 offset) override;
        int64 Tell() override;
        size_t Length() override;
    };

}