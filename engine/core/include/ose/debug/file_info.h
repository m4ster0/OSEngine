#pragma once

#include "ose/typedef.h"

namespace ose::debug {

    //SourceFileInfo is meant to be used only as temp object
    struct FileInfo
    {
        const char* c_file;
        const OSEint c_line;
        inline FileInfo(const char* file, OSEint line)
            : c_file{ file }, c_line{ line }
        {

        }
    };

}