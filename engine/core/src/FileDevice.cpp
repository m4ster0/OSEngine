#include "OSE/System/FileDevice.h"

namespace OSE {

    FileDevice::FileDevice(const std::string& type, FileMode mode) :
        m_Type{ type }, m_Mode { mode }
    {
    }

    FileDevice::~FileDevice()
    {
    }

    const std::string& FileDevice::GetType() const
    {
        return m_Type;
    }

    bool FileDevice::FileModeAvailable(FileMode mode) const
    {
        return static_cast<bool>(m_Mode & mode);
    }

    bool FileDevice::CreateDir(const std::string& path)
    {
        if (FileModeAvailable(FileMode::Create))
            return CreateDirInternal(path);

        return false;
    }

    std::unique_ptr<File> FileDevice::OpenFileSync(const std::string& path, FileMode mode)
    {
        if (FileModeAvailable(mode))
            return OpenFileSyncInternal(path, mode);

        return nullptr;
    }
}