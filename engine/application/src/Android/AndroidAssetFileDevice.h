#pragma once

#include "OSE/System/FileDevice.h"

#include <android/asset_manager.h>

namespace OSE {

    class AndroidAssetFileDevice: public FileDevice
    {
        ::AAssetManager* m_Mgr;

    public:
        AndroidAssetFileDevice(::AAssetManager* mgr);
        ~AndroidAssetFileDevice();

        virtual bool FileExists(const std::string& path) const override;
        virtual bool DirExists(const std::string& path) const override;
        virtual bool DirFiles(const std::string& path, std::vector<std::string>& dirEntries) const override;

    protected:
        virtual bool CreateDirInternal(const std::string& fullPath) override;
        virtual std::unique_ptr<File> OpenFileSyncInternal(const std::string& fullPath, FileMode mode) override;
    };

}