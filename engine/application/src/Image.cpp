#include "OSE/Resources/Image.h"

#include <utility>

namespace OSE {

    static size_t formatToPixelSize(Image::Format format)
    {
        switch (format)
        {
        case Image::Format::RGB:
            return 24;
        case Image::Format::RGBA:
            return 32;
        }
    }

    Image::Image(std::unique_ptr<byte[], deleter> data, size_t width, size_t height, Format format):
        m_Data{ std::move(data) }, m_Width{ width }, m_Height{ height }, m_Format{ format }
    {
        m_PixelSize = formatToPixelSize(format);
    }

    Image::Image(std::unique_ptr<byte[], deleter> data, size_t size, Format format):
        m_Data{ std::move(data) }, m_Width{ size }, m_Height{ size }, m_Format{ format }
    {
        m_PixelSize = formatToPixelSize(format);
    }

    void Image::Dispose()
    {
        m_Data = nullptr;
        m_PixelSize = 0;

        m_Width = 0;
        m_Height = 0;
    }

}