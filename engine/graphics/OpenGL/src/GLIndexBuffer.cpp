#include "OSE/Graphics/GLIndexBuffer.h"
#include "OSE/Graphics/GLCommon.h"

namespace OSE {
    GLIndexBuffer::GLIndexBuffer(size_t size, bool isStatic) :
        GLBuffer(size, sizeof(uint16), isStatic)
    {
        GLCall(glGenBuffers(1, &m_Handle));
        OSE_ASSERT(m_Handle, "Could not create vertex buffer");

        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_ByteSize, nullptr, m_IsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    GLIndexBuffer::~GLIndexBuffer()
    {
        Dispose();
    }

    void GLIndexBuffer::Write(const byte* data)
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_ByteSize, data, m_IsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
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