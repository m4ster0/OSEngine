#pragma once

#include <OSE/TypeDefs.h>

#include <unordered_map>
#include <string>
#include <vector>

namespace OSE {
    struct GLVertexAttribute
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

    class GLVertexDescriptor
    {
    public:
        GLVertexDescriptor(const std::vector<GLVertexAttribute>& attributes);

        const std::vector<GLVertexAttribute>& GetAttributes() const
        {
            return m_Attributes;
        }

        size_t GetSize() const
        {
            return m_Size;
        }

        size_t GetByteSize() const
        {
            return m_Size * sizeof(float);
        }

    private:
        std::vector<GLVertexAttribute> m_Attributes;
        size_t m_Size{ 0 };
    };
}