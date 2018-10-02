#include "OSE/Resources/ImageFactory.h"

#define STBI_NO_STDIO
#define STBI_NO_GIF
#define STBI_NO_PSD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <utility>
#include <functional>

namespace OSE {

    namespace ImageFactory {

        static int formatToNumChannels(Image::Format format)
        {
            using ImgFormat = Image::Format;
            switch (format)
            {
            case ImgFormat::RGB:
                return STBI_rgb;
            case ImgFormat::RGBA:
                return STBI_rgb_alpha;
            }
        }

        std::unique_ptr<Image> decode(const FileSystem& fileSystem, const std::string& device, const std::string & path, const DecodeOptions& options)
        {
            std::unique_ptr<File> file = fileSystem.OpenFileSync(device, path, FileMode::Read);
            if (file)
                return decode(*file, options);

            return nullptr;
        }

        std::unique_ptr<Image> decode(File& file, const DecodeOptions& options)
        {
            stbi_io_callbacks callbacks{};
            callbacks.read = [](void *user, char *data, int size) -> int {
                File* file = static_cast<File*>(user);
                return file->Read((byte*) data, size);
            };
            callbacks.skip = [](void *user, int n) {
                File* file = static_cast<File*>(user);
                file->SeekCurrent(n);
            };
            callbacks.eof = [](void *user) -> int {
                File* file = static_cast<File*>(user);
                return file->Tell() == file->Length();
            };

            int channels = formatToNumChannels(options.format);
            int width, height, srcChannels;

            stbi_set_flip_vertically_on_load(options.flipY);

            byte* stbiData = stbi_load_from_callbacks(&callbacks, (void*) &file, &width, &height, &srcChannels, channels);
            std::unique_ptr<byte[], Image::deleter> imgData{ stbiData, [](byte bytes[]) {
                stbi_image_free(bytes);
            }};
            if (imgData == nullptr)
                return nullptr;

            return std::unique_ptr<Image>{ new Image(std::move(imgData), width, height, options.format) };
        }

        std::unique_ptr<Image> decode(const byte* data, size_t length, const DecodeOptions& options)
        {
            int channels = formatToNumChannels(options.format);
            int width, height, srcChannels;

            stbi_set_flip_vertically_on_load(options.flipY);

            byte* stbiData = stbi_load_from_memory(data, length, &width, &height, &srcChannels, channels);
            std::unique_ptr<byte[], Image::deleter> imgData{ stbiData, [](byte bytes[]) {
                stbi_image_free(bytes);
            }};
            if (imgData == nullptr)
                return nullptr;

            return std::unique_ptr<Image>{ new Image(std::move(imgData), width, height, options.format) };
        }

    }

}