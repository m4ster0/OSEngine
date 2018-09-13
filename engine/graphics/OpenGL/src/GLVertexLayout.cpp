
#include "OSE/Graphics/GLVertexLayout.h"
#include "OSE/Graphics/GLCommon.h"

namespace OSE {

    GLVertexLayout::GLVertexLayout(const std::vector<VertexAttributeDescriptor>& attributes) :
        m_Attributes{ attributes }
    {
        for (const VertexAttributeDescriptor& attr : m_Attributes)
            m_Size += attr.size;
    }

    void GLVertexLayout::Bind() const
    {
        size_t offset{ 0 };
        for (const auto& attr : m_Attributes)
        {
            uint pos = static_cast<uint>(attr.type);
            GLCall(glEnableVertexAttribArray(pos));
            GLCall(glVertexAttribPointer(pos, attr.size, GL_FLOAT, attr.normalized, GetByteSize(), (const void*)offset));
            offset += (attr.size * sizeof(float));
        }
    }
}