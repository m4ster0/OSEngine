#include "Win32File.h"

namespace OSE {

    Win32FileSync::Win32FileSync(HANDLE file) :
        m_File{ file }
    {

    }

    Win32FileSync::~Win32FileSync()
    {
        CloseHandle(m_File);
    }

    size_t Win32FileSync::Read(byte* buffer, size_t length)
    {
        size_t readLength;
        ReadFile(m_File, buffer, length, (LPDWORD) &readLength, NULL);
        return readLength;
    }

    size_t Win32FileSync::Write(const byte* buffer, size_t length)
    {
        size_t writeLength;
        WriteFile(m_File, buffer, length, (LPDWORD) &writeLength, NULL);
        return writeLength;
    }

    bool Win32FileSync::Seek(size_t position)
    {
        LARGE_INTEGER offset{ position };
        LARGE_INTEGER result{ 0 };
        SetFilePointerEx(m_File, offset, &result, FILE_BEGIN);

        return offset.QuadPart == result.QuadPart;
    }

    bool Win32FileSync::SeekCurrent(int64 offset)
    {
        LARGE_INTEGER winOffset{ offset };
        LARGE_INTEGER result{ 0 };
        SetFilePointerEx(m_File, winOffset, &result, FILE_CURRENT);

        return winOffset.QuadPart == result.QuadPart;
    }

    int64 Win32FileSync::Tell()
    {
        LARGE_INTEGER offset{ 0 };
        LARGE_INTEGER currentPos{ 0 };
        SetFilePointerEx(m_File, offset, &currentPos, FILE_CURRENT);
        return currentPos.QuadPart;
    }

    size_t Win32FileSync::Length()
    {
        LARGE_INTEGER size{ 0 };
        GetFileSizeEx(m_File, &size);
        return size.QuadPart;
    }
}