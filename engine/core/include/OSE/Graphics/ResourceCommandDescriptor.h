#pragma once

#include "OSE/TypeDefs.h"

#include <string>
#include <unordered_map>

namespace OSE {

    struct ShaderDescriptor
    {
        enum class Type
        {
            Vertex,
            Fragment
        };

        Type type;
        std::string src;
    };

    struct VertexAttributeDescriptor
    {
        enum class Type : uint
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

    struct BufferDescriptor
    {
        size_t byteSize;
        size_t size;
        bool IsStatic;
    };

    struct BufferDataDescriptor
    {
        std::unique_ptr<byte[]> data{ nullptr };
        size_t length{ 0 };
        size_t offset{ 0 };
        bool discardAll{ false };
    };
}