#include "OSE/Graphics/GLVertexBuffer.h"
#include "OSE/Graphics/GLcommon.h"

namespace OSE {
    GLVertexBuffer::GLVertexBuffer(size_t size, bool isStatic) :
        GLBuffer(size, isStatic)
    {
        GLCall(glGenBuffers(1, &m_Handle));
        OSE_ASSERT(m_Handle, "Could not create vertex buffer");

        WriteData(nullptr);
    }

    GLVertexBuffer::~GLVertexBuffer()
    {
        Dispose();
    }

    void GLVertexBuffer::WriteData(const byte* data)
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
        GLCall(glBufferData(GL_ARRAY_BUFFER, m_ByteSize, data, m_IsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void GLVertexBuffer::WriteSubData(const byte* data, size_t length, size_t offset)
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, length, data));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
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