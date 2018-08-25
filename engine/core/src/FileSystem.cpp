#include "OSE/System/FileSystem.h"

#include <algorithm>

namespace OSE {

    FileSystem::DeviceList FileSystem::s_SharedDevices{ };

    static auto FindDevice(const FileSystem::DeviceList& deviceList, const FileDevice& device)
    {
        return std::find_if(deviceList.begin(),
                            deviceList.end(),
                            [&](const FileSystem::DeviceRef& deviceRef) -> bool { return &deviceRef.get() == &device; });
    }

    void FileSystem::MountShared(FileDevice& device)
    {
        auto it = FindDevice(s_SharedDevices, device);
        if(it == s_SharedDevices.end())
            s_SharedDevices.push_back(device);
    }

    void FileSystem::UnmountShared(FileDevice& device)
    {
        auto it = FindDevice(s_SharedDevices, device);
        if(it != s_SharedDevices.end())
            s_SharedDevices.erase(it);
    }

    FileSystem::FileSystem():
        m_Devices{ s_SharedDevices }
    {

    }

    FileSystem::~FileSystem()
    {

    }

    void FileSystem::Mount(FileDevice &device)
    {
        auto it = FindDevice(m_Devices, device);
        if(it == m_Devices.end())
            m_Devices.push_back(device);
    }

    void FileSystem::Unmount(FileDevice &device)
    {
        auto it = FindDevice(m_Devices, device);
        if(it != m_Devices.end())
            m_Devices.erase(it);
    }

    bool FileSystem::FileExists(const std::string &deviceType, const std::string &path) const
    {
        for ( auto i = m_Devices.begin(); i != m_Devices.end(); i++ )
        {
            FileDevice& device = (*i).get();
            if (device.GetType() == deviceType)
                return device.FileExists(path);
        }

        return false;
    }

    bool FileSystem::DirExists(const std::string &deviceType, const std::string &path) const
    {
        for ( auto i = m_Devices.begin(); i != m_Devices.end(); i++ )
        {
            FileDevice& device = (*i).get();
            if (device.GetType() == deviceType)
                return device.DirExists(path);
        }

        return false;
    }

    bool FileSystem::DirFiles(const std::string &deviceType, const std::string &path, std::vector<std::string>& dirEntries) const
    {
        for ( auto i = m_Devices.begin(); i != m_Devices.end(); i++)
        {
            FileDevice& device = (*i).get();
            if (device.GetType() == deviceType)
                return device.DirFiles(path, dirEntries);
        }

        return false;
    }

    bool FileSystem::CreateDir(const std::string &deviceType, const std::string &path) const
    {
        for ( auto i = m_Devices.begin(); i != m_Devices.end(); i++)
        {
            FileDevice& device = (*i).get();
            if (device.GetType() == deviceType)
                return device.CreateDir(path);
        }

        return false;
    }

    std::unique_ptr<File> FileSystem::OpenFileSync(const std::string &deviceType, const std::string &path, FileMode mode) const
    {
        for ( auto i = m_Devices.begin(); i != m_Devices.end(); i++)
        {
            FileDevice& device = (*i).get();
            if (device.GetType() == deviceType)
                return device.OpenFileSync(path, mode);
        }

        return nullptr;
    }


}