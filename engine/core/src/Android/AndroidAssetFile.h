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

        virtual size_t Read(byte* buffer, size_t length) override;
        virtual size_t Write(const byte* buffer, size_t length) override;

        virtual bool Seek(size_t position) override;
        virtual int64 Tell() override;
        virtual size_t Length() override;
    };

}
