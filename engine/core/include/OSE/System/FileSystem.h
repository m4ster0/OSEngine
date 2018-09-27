#pragma once

#include "OSE/System/File.h"
#include "OSE/System/FileDevice.h"


#include <string>
#include <vector>
#include <memory>

namespace OSE {

    //TODO add tests for whole filesystem
    class FileSystem
    {
    public:
        using DeviceRef = std::reference_wrapper<FileDevice>;
        using DeviceList = std::vector<DeviceRef>;

        static void MountShared(FileDevice& device);
        static void UnmountShared(FileDevice& device);

        FileSystem();
        ~FileSystem();

        void Mount(FileDevice& device);
        void Unmount(FileDevice& device);

        bool FileExists(const std::string& devicePath) const;
        bool FileExists(const std::string& deviceType, const std::string& path) const;

        bool DirExists(const std::string& devicePath) const;
        bool DirExists(const std::string& deviceType, const std::string& path) const;

        bool DirFiles(const std::string& devicePath, std::vector<std::string>& dirEntires) const;
        bool DirFiles(const std::string& deviceType, const std::string& path, std::vector<std::string>& dirEntries) const;


        bool CreateDir(const std::string& devicePath) const;
        bool CreateDir(const std::string& deviceType, const std::string& path) const;

        std::unique_ptr<File> OpenFileSync(const std::string& devicePath, FileMode mode) const;
        std::unique_ptr<File> OpenFileSync(const std::string& deviceType, const std::string& path, FileMode mode) const;
        //std::option<File> OpenFileSync(const std::string& devicePath, FileMode mode) const;
        //std::option<File> OpenFileSync(const std::string& deviceType, const std::string& path, FileMode mode) const;

    private:
        static DeviceList s_SharedDevices;

        DeviceList m_Devices{ };
    };

}
