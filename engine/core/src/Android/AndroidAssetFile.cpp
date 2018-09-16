#include "AndroidAssetFile.h"

#include <android/asset_manager.h>
#include <cstdio>

namespace OSE {

    AndroidAssetFileSync::AndroidAssetFileSync(::AAsset *asset):
        m_Asset{ asset }
    {
    }

    AndroidAssetFileSync::~AndroidAssetFileSync()
    {
        ::AAsset_close(m_Asset);
    }

    size_t AndroidAssetFileSync::Read(byte *buffer, size_t length)
    {
        int result = ::AAsset_read(m_Asset, buffer, length);
        return result >= 0 ? (size_t) result : 0;
    }

    size_t AndroidAssetFileSync::Write(const byte*, size_t)
    {
        return 0;
    }

    bool AndroidAssetFileSync::Seek(size_t position)
    {
        int64 result = ::AAsset_seek64(m_Asset, position, SEEK_SET);
        return result == position;
    }

    bool AndroidAssetFileSync::SeekCurrent(int64 offset)
    {
        int64 result = ::AAsset_seek64(m_Asset, offset, SEEK_CUR);
        return result == position;
    }

    int64 AndroidAssetFileSync::Tell()
    {
        return ::AAsset_getLength64(m_Asset) - ::AAsset_getRemainingLength64(m_Asset);
    }

    size_t AndroidAssetFileSync::Length()
    {
        return (size_t) ::AAsset_getLength64(m_Asset);
    }
}