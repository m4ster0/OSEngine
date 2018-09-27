
#include "OSE/Graphics/GLVertexArray.h"

#include "OSE/Graphics/GLCommon.h"

namespace OSE {

    GLVertexArray::GLVertexArrayObject::GLVertexArrayObject()
    {
        GLCall(glGenVertexArrays(1, &handle));
    }

    GLVertexArray::GLVertexArrayObject::~GLVertexArrayObject()
    {
        GLCall(glDeleteVertexArrays(1, &handle));
    }

    GLVertexArray::GLVertexArray(int32 id, const std::vector<VertexAttributeDescriptor>& attributes):
        GLResource(id), m_Layout{ attributes }
    {

    }

    GLVertexArray::~GLVertexArray()
    {
        Dispose();
    }

    void GLVertexArray::BindVerbose(const GLBuffer& vbo, const GLBuffer* ibo)
    {
        vbo.Bind();
        m_Layout.Bind();
        if (ibo) ibo->Bind();
    }

    int64 GLVertexArray::GetVAOHandle(const GLBuffer& vbo, const GLBuffer* ibo)
    {
        if (vbo.rid && (ibo == nullptr || ibo->rid))
        {
            int64 handle = vbo.rid;
            if (ibo) handle |= (static_cast<int64>(ibo->rid) << 32);

            return handle;
        }

        return -1;
    }

    size_t GLVertexArray::BindInternal(const GLBuffer& vbo, const GLBuffer* ibo, size_t count)
    {
        int64 vaoHandle = GetVAOHandle(vbo, ibo);
        auto it = m_VAOs.find(vaoHandle);
        if (vaoHandle >= 0 && it != m_VAOs.end())
        {
            GLCall(glBindVertexArray(it->second->handle));
            return count;

        }

        GLCall(glBindVertexArray(0));
        BindVerbose(vbo, ibo);

        return count;
    }

    void GLVertexArray::MakeVAOInternal(const GLBuffer& vbo, const GLBuffer* ibo)
    {
        if (oseCheckGLExtension<oseGLExtension::VertexArrayObject>())
        {
            int64 vaoHandle = GetVAOHandle(vbo, ibo);
            auto it = m_VAOs.find(vaoHandle);
            if (vaoHandle >= 0 && it == m_VAOs.end())
            {
                m_VAOs[vaoHandle] = std::unique_ptr<GLVertexArrayObject>{ new GLVertexArrayObject };
                GLCall(glBindVertexArray(m_VAOs[vaoHandle]->handle));
                BindVerbose(vbo, ibo);
            }
        }
    }

    void GLVertexArray::MakeVAO(const GLBuffer& vbo)
    {
        MakeVAOInternal(vbo, nullptr);
    }

    void GLVertexArray::MakeVAO(const GLBuffer& vbo, const GLBuffer& ibo)
    {
        MakeVAOInternal(vbo, &ibo);
    }

    size_t GLVertexArray::Bind(const GLBuffer& vbo)
    {
        size_t vertexCount = vbo.GetSize() / m_Layout.GetSize();
        return BindInternal(vbo, nullptr, vertexCount);
    }

    size_t GLVertexArray::BindIndexed(const GLBuffer& vbo, const GLBuffer& ibo)
    {
        return BindInternal(vbo, &ibo, ibo.GetSize());
    }

    void GLVertexArray::Dispose()
    {
        m_VAOs.clear();
    }
}