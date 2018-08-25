#include "OSE/System/FileDiskDevice.h"
#include "Win32File.h"

#include <Windows.h>

#include <sstream>

namespace OSE {

    FileDiskDevice::FileDiskDevice(const std::string& type, FileMode mode):
            FileDevice{ type, mode }
    {

    }

    FileDiskDevice::~FileDiskDevice()
    {

    }

    bool FileDiskDevice::FileExists(const std::string& fullPath) const
    {
        DWORD dwAttrib = GetFileAttributes(fullPath.c_str());
        return dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
    }

    bool FileDiskDevice::DirExists(const std::string& fullPath) const
    {
        DWORD dwAttrib = GetFileAttributes(fullPath.c_str());
        return dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
    }

    bool FileDiskDevice::DirFiles(const std::string& fullPath, std::vector<std::string>& dirEntries) const
    {
        std::stringstream ss{ };
        ss << fullPath << '/' << '*';
        std::string searchPath = ss.str();
        WIN32_FIND_DATA findData{ };
        HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            dirEntries.push_back(findData.cFileName);
            while (FindNextFile(hFind, &findData) != FALSE)
                dirEntries.push_back(findData.cFileName);

            FindClose(hFind);
            return true;
        }

        return false;
    }

    //TODO add dir tree getter from path
    bool FileDiskDevice::CreateDirInternal(const std::string& fullPath)
    {
        return false;
    }

    static DWORD GetFileAccessMode(FileMode);
    static DWORD GetFileCreationMode(FileMode);

    std::unique_ptr<File> FileDiskDevice::OpenFileSyncInternal(const std::string& fullPath, FileMode mode)
    {
        HANDLE hFile = CreateFile(fullPath.c_str(),
            GetFileAccessMode(mode),
            FILE_SHARE_READ, // potentially add file_share_write?
            NULL,
            GetFileCreationMode(mode),
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (hFile != INVALID_HANDLE_VALUE)
            return std::unique_ptr<File>{ new Win32FileSync{ hFile } };

        return nullptr;
    }

    static DWORD GetFileAccessMode(FileMode mode)
    {
        DWORD accessMode = GENERIC_READ;
        if (static_cast<bool>(mode & FileMode::Write))
            accessMode |= GENERIC_WRITE;

        return accessMode;
    }

    static DWORD GetFileCreationMode(FileMode mode)
    {
        if (static_cast<bool>(mode & FileMode::Create))
            return OPEN_ALWAYS;

        return OPEN_EXISTING;
    }
}