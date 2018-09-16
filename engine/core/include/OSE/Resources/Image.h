#pragma once

#include "OSE/TypeDefs.h"

#include <memory>
#include <functional>

namespace OSE {

    //represents uncompressed cpu memory image
    class Image
    {
    public:
        enum class Format
        {
            RGB, //8 bits per channel
            RGBA //8 bits per channel
        };

        using deleter = std::function<void(byte[])>;
        Image(std::unique_ptr<byte[], deleter> data, size_t width, size_t height, Format format);
        Image(std::unique_ptr<byte[], deleter> data, size_t size, Format format);

        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;

        inline Format GetFormat() const { return m_Format; }

        inline size_t GetWidth() const { return m_Width; }
        inline size_t GetHeight() const { return m_Height; }

        inline byte* GetData() const { return m_Data.get(); }

        void Dispose();

    private:
        Format m_Format;
        size_t m_PixelSize{ 0 };

        size_t m_Width{ 0 };
        size_t m_Height{ 0 };

        std::unique_ptr<byte[], deleter> m_Data{ nullptr };
    };

}