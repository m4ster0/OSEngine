#pragma once

#include <OSE/TypeDefs.h>

#include <vector>

namespace OSE {

    class GLVertexDescriptor
    {
    public:
        struct Attribute
        {
            size_t offset;
        public:
            enum class Type
            {
                Position,
                Normal,
                Color,
                TexCoord0,
                TexCoord1
            };

            Type type;
            uint size;
            bool normalized;
        };

        GLVertexDescriptor(const std::vector<Attribute>& attributes);
        GLVertexDescriptor(std::vector<Attribute>&& attributes);

    private:
        std::vector<Attribute> m_Attributes;
        size_t m_Stride;
    };

}