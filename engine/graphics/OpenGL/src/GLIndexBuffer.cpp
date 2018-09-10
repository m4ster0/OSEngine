#include "OSE/Graphics/GLIndexBuffer.h"
#include "OSE/Graphics/GLCommon.h"

namespace OSE {
    GLIndexBuffer::GLIndexBuffer(size_t size, bool isStatic) :
        GLBuffer(size, isStatic)
    {
        GLCall(glGenBuffers(1, &m_Handle));
        OSE_ASSERT(m_Handle, "Could not create vertex buffer");

        WriteData(nullptr);
    }

    GLIndexBuffer::~GLIndexBuffer()
    {
        Dispose();
    }

    void GLIndexBuffer::WriteData(const byte* data)
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_ByteSize, data, m_IsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void GLIndexBuffer::WriteSubData(const byte* data, size_t length, size_t offset)
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
        GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, length, data));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void GLIndexBuffer::Dispose()
    {
        if (m_Handle)
        {
            glDeleteBuffers(1, &m_Handle);
            m_Handle = 0;
        }
    }
}