#include "OSE/Graphics/GLVertexBuffer.h"
#include "OSE/Graphics/GLcommon.h"

namespace OSE {
    void GLVertexBuffer::Clear()
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    GLVertexBuffer::GLVertexBuffer(size_t size, size_t vertexByteSize, bool isStatic) :
        GLBuffer(size, vertexByteSize, isStatic)
    {
        GLCall(glGenBuffers(1, &m_Handle));
        OSE_ASSERT(m_Handle, "Could not create vertex buffer");

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
        GLCall(glBufferData(GL_ARRAY_BUFFER, m_ByteSize, nullptr, m_IsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void GLVertexBuffer::Write(const byte* data)
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
        GLCall(glBufferData(GL_ARRAY_BUFFER, m_ByteSize, data, m_IsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void GLVertexBuffer::Bind()
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
    }

    void GLVertexBuffer::Dispose()
    {
        if (m_Handle)
        {
            glDeleteBuffers(1, &m_Handle);
            m_Handle = 0;
        }
    }
}