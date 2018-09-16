#pragma once

#include "OSE/Resources/Image.h"
#include "OSE/System/FileSystem.h"
#include "OSE/System/File.h"
#include "OSE/TypeDefs.h"

#include <memory>
#include <string>

namespace OSE {

    namespace ImageFactory
    {
        struct DecodeOptions
        {
            Image::Format format{ Image::Format::RGB };
            bool flipY{ false };
        };

        std::unique_ptr<Image> Decode(const FileSystem& fileSystem, const std::string& device, const std::string& path, const DecodeOptions& options = DecodeOptions{});
        std::unique_ptr<Image> Decode(File& file, const DecodeOptions& options = DecodeOptions{});
        std::unique_ptr<Image> Decode(const byte* data, size_t length, const DecodeOptions& options = DecodeOptions{});
    }

}