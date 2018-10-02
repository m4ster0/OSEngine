
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

    void GLVertexArray::BindArrays(const GLBuffer& vbo, const GLBuffer* ibo)
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

    void GLVertexArray::BindInternal(const GLBuffer & vbo, const GLBuffer * ibo)
    {
        if (oseCheckGLExtension<oseGLExtension::VertexArrayObject>())
            BindVAO(vbo, ibo);
        else
            BindArrays(vbo, ibo);
    }


    void GLVertexArray::BindVAO(const GLBuffer& vbo, const GLBuffer* ibo)
    {
        int64 vaoHandle = GetVAOHandle(vbo, ibo);
        auto it = m_VAOs.find(vaoHandle);
        if (vaoHandle >= 0 && it != m_VAOs.end())
        {
            GLCall(glBindVertexArray(it->second->handle));
        }
        else
        {
            GLCall(glBindVertexArray(0));
            BindArrays(vbo, ibo);
        }

    }

    void GLVertexArray::MakeVAO(const GLBuffer& vbo, const GLBuffer* ibo)
    {
        if (oseCheckGLExtension<oseGLExtension::VertexArrayObject>())
        {
            int64 vaoHandle = GetVAOHandle(vbo, ibo);
            auto it = m_VAOs.find(vaoHandle);
            if (vaoHandle >= 0 && it == m_VAOs.end())
            {
                m_VAOs[vaoHandle] = std::unique_ptr<GLVertexArrayObject>{ new GLVertexArrayObject };
                GLCall(glBindVertexArray(m_VAOs[vaoHandle]->handle));
                BindArrays(vbo, ibo);
            }
        }
    }

    size_t GLVertexArray::Bind(const GLBuffer& vbo)
    {
        size_t vertexCount = vbo.GetSize() / m_Layout.GetSize();
        BindInternal(vbo, nullptr);
        return vertexCount;
    }

    size_t GLVertexArray::BindIndexed(const GLBuffer& vbo, const GLBuffer& ibo)
    {
        BindInternal(vbo, &ibo);
        return ibo.GetSize();
    }

    void GLVertexArray::Dispose()
    {
        m_VAOs.clear();
    }
}