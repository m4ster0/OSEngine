#include "OSE/Graphics/GLVertexDescriptor.h"

namespace OSE {
    using AttrType = GLVertexAttribute::Type;

    std::unordered_map<AttrType, std::string> GLVertexAttribute::TypeName = {
        {AttrType::Position     , "aPosition"},
        {AttrType::Normal       , "aNormal"},
        {AttrType::Color        , "aColor"},
        {AttrType::TexCoord0    , "aTexCoord0"},
        {AttrType::TexCoord1    , "aTexCoord1"}
    };

    GLVertexDescriptor::GLVertexDescriptor(const std::vector<GLVertexAttribute>& attributes) :
        m_Attributes{ attributes }
    {
        for (const GLVertexAttribute& attr : m_Attributes)
            m_Size += attr.size;
    }
}