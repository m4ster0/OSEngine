#include "OSE/System/FileDiskDevice.h"
#include "PosixFile.h"

#include <cstdio>
#include <sys/stat.h>
#include <dirent.h>

namespace OSE {

    FileDiskDevice::FileDiskDevice(const std::string& type, FileMode mode):
            FileDevice{ type, mode }
    {

    }

    FileDiskDevice::~FileDiskDevice()
    {

    }

    bool FileDiskDevice::FileExists(const std::string &path) const
    {
        struct stat info{};
        return ::stat(path.c_str(), &info) != 0 && (info.st_mode & S_IFREG);
    }

    bool FileDiskDevice::DirExists(const std::string &path) const
    {
        struct stat info{};
        return ::stat(path.c_str(), &info) != 0 && (info.st_mode & S_IFDIR);
    }

    bool FileDiskDevice::DirFiles(const std::string &path, std::vector<std::string>& dirEntries) const
    {
        ::DIR* dir;
        if((dir = ::opendir(path.c_str())) != NULL)
        {
            ::dirent* dirEntry;
            while((dirEntry = ::readdir(dir)) != NULL)
            {
                if(dirEntry->d_type == DT_REG)
                    dirEntries.push_back(dirEntry->d_name);
            }

            ::closedir(dir);
            return true;
        }

        return false;
    }

    bool FileDiskDevice::CreateDirInternal(const std::string &fullPath)
    {
        return false;
    }

    static std::string GetFileAccessMode(FileMode);

    std::unique_ptr<File> FileDiskDevice::OpenFileSyncInternal(const std::string &fullPath, FileMode mode)
    {
        if(static_cast<bool>(mode & FileMode::Create) && !FileExists(fullPath))
        {
            ::FILE* touchFile = ::fopen(fullPath.c_str(), "wb");
            if(touchFile == nullptr)
                return nullptr;

            ::fclose(touchFile);
        }

        std::string accessMode{ GetFileAccessMode(mode) };
        ::FILE* file = ::fopen(fullPath.c_str(), accessMode.c_str());
        if(file != nullptr)
            return std::unique_ptr<File>{ new PosixFileSync{ file } };

        return nullptr;
    }

    static std::string GetFileAccessMode(FileMode mode)
    {
        if(static_cast<bool>(mode & FileMode::Write))
            return "r+b";

        return "rb";
    }
}