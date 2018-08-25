#include "PosixFile.h"

namespace OSE {


    PosixFileSync::PosixFileSync(::FILE* file):
        m_File{ file }
    {
    }

    PosixFileSync::~PosixFileSync()
    {
        ::fclose(m_File);
    }

    size_t PosixFileSync::Read(byte *buffer, size_t length)
    {
        size_t result = ::fread(buffer, sizeof(byte), length, m_File);
        return result;
    }

    size_t PosixFileSync::Write(const byte *buffer, size_t length)
    {
        size_t result = ::fwrite(buffer, sizeof(byte), length, m_File);
        return result;
    }

    bool PosixFileSync::Seek(size_t position)
    {
        return ::fseek(m_File, position, SEEK_SET) == 0;
    }

    int64 PosixFileSync::Tell()
    {
        return ::ftell(m_File);
    }

    size_t PosixFileSync::Length()
    {
        size_t length = 0;
        if(::fseek(m_File, 0, SEEK_END) == 0)
        {
            int64 position = Tell();
            length = position >= 0 ? (size_t) position : 0;
            ::fseek(m_File, 0, SEEK_SET);
        }

        return length;
    }

}