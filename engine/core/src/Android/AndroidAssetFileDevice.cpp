#include "AndroidAssetFileDevice.h"
#include "AndroidAssetFile.h"

namespace OSE {

    AndroidAssetFileDevice::AndroidAssetFileDevice(::AAssetManager *mgr):
        FileDevice{ "assets", FileMode::Read }, m_Mgr{ mgr }
    {
    }

    AndroidAssetFileDevice::~AndroidAssetFileDevice()
    {
    }

    bool AndroidAssetFileDevice::FileExists(const std::string &path) const
    {
        return false;
    }

    bool AndroidAssetFileDevice::DirExists(const std::string &path) const
    {
        return false;
    }

    bool AndroidAssetFileDevice::DirFiles(const std::string &path, std::vector<std::string>& dirEntries) const
    {
        return false;
    }

    bool AndroidAssetFileDevice::CreateDirInternal(const std::string &fullPath)
    {
        return false;
    }

    std::unique_ptr<File> AndroidAssetFileDevice::OpenFileSyncInternal(const std::string &fullPath, FileMode)
    {
        ::AAsset* asset = ::AAssetManager_open(m_Mgr, fullPath.c_str(), ::AASSET_MODE_RANDOM);
        if(asset != nullptr)
            return std::unique_ptr<File>{ new AndroidAssetFileSync{ asset } };

        return nullptr;
    }
}