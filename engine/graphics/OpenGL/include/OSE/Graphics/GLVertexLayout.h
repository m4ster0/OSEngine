#pragma once

#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/TypeDefs.h>

#include <vector>

namespace OSE {

    class GLVertexLayout
    {
        std::vector<VertexAttributeDescriptor> m_Attributes;
        size_t m_Size{ 0 };
    public:
        GLVertexLayout(const std::vector<VertexAttributeDescriptor>& attributes);

        void Bind() const;

        inline size_t GetSize() const { return m_Size; }
        inline size_t GetByteSize() const { return m_Size * sizeof(float); }
    };
}