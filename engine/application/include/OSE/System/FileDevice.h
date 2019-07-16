#pragma once
#include "OSE/System/File.h"

#include <string>
#include <vector>
#include <memory>

namespace OSE {

    class FileDevice
    {
    public:
        FileDevice(const std::string& type, FileMode mode);
        virtual ~FileDevice();

        const std::string& GetType() const;
        bool FileModeAvailable(FileMode mode) const;

        virtual bool FileExists(const std::string& path) const = 0;
        virtual bool DirExists(const std::string& path) const = 0;
        virtual bool DirFiles(const std::string& path, std::vector<std::string>& dirEntries) const = 0;

        bool CreateDir(const std::string& path);
        std::unique_ptr<File> OpenFileSync(const std::string& path, FileMode mode);

    protected:
        std::string m_Type;
        FileMode m_Mode;

        virtual bool CreateDirInternal(const std::string& fullPath) = 0;
        virtual std::unique_ptr<File> OpenFileSyncInternal(const std::string& fullPath, FileMode mode) = 0;
    };

}