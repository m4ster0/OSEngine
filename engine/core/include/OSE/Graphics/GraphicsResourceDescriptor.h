#pragma once

#include "OSE/TypeDefs.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace OSE {

    struct ShaderDescriptor
    {
        enum class Type: byte
        {
            Vertex,
            Fragment
        };

        Type type;
        std::string src;
    };

    std::vector<ShaderDescriptor> shaderDescriptorsFromSources(const std::string& vertSrc, const std::string& fragSrc);
    std::vector<ShaderDescriptor> shaderDescriptorsFromSource(const std::string& singleSrc);

    struct VertexAttributeDescriptor
    {
        enum class Type : byte
        {
            Position = 0,
            Normal,
            Color,
            TexCoord0,
            TexCoord1
        };

        static std::unordered_map<Type, std::string> TypeName;

        Type type;
        size_t size{ 0 };
        bool normalized{ false };
    };

    struct BufferDataDescriptor
    {
        const byte* data;
        size_t length;
        size_t offset{ 0 };
        bool discardAll{ false };
    };

    struct BufferDescriptor
    {
        enum class Type : byte
        {
            Vertex,
            Index
        };

        size_t byteSize;
        size_t size;
        bool isStatic;
    };

    struct TextureDescriptor
    {
        enum class Wrap : byte
        {
            Repeat,
            MirrorRepeat,
            EdgeClamp,
            BorderClamp
        };

        enum class Filter : byte
        {
            Nearest,
            Linear
        };

        Wrap wrap{ Wrap::Repeat };
        Filter minifyFilter{ Filter::Nearest };
        Filter magnifyFilter{ Filter::Nearest };
    };

    using ShaderType = ShaderDescriptor::Type;
    using VertexAttrType = VertexAttributeDescriptor::Type;
    using BufferType = BufferDescriptor::Type;
    using TexWrapType = TextureDescriptor::Wrap;
    using TexFilterType = TextureDescriptor::Filter;
}