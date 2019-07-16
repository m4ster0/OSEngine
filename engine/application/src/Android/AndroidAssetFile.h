#pragma once

#include "OSE/System/File.h"
#include "OSE/TypeDefs.h"

struct AAsset;

namespace OSE {

    class AndroidAssetFileSync: public File
    {
        ::AAsset* m_Asset{ nullptr };

    public:
        AndroidAssetFileSync(::AAsset* asset);
        ~AndroidAssetFileSync();

        size_t Read(byte* buffer, size_t length) override;
        size_t Write(const byte* buffer, size_t length) override;

        bool Seek(size_t position) override;
        bool SeekCurrent(int64 offset) override;
        int64 Tell() override;
        size_t Length() override;
    };

}
