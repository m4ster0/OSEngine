#include "OSE/System/File.h"

namespace OSE {

    bool File::Read(std::string& buffer)
    {
        size_t length = Length();
        buffer.resize(length);

        Seek(0);
        size_t readLength = Read((byte*) &(buffer[0]), length);

        return readLength == length;
    }

    bool File::Write(const std::string& buffer)
    {
        size_t length = buffer.size();
        size_t writeLength = Write((const byte*) &(buffer[0]), length);

        return writeLength == length;
    }

}