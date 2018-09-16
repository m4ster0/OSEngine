
#include "OSE/Graphics/GLBuffer.h"
#include "OSE/Graphics/GLCommon.h"

namespace OSE {
    static uint GetGLBufferType(BufferType type)
    {
        switch (type)
        {
        case BufferType::Vertex:
            return GL_ARRAY_BUFFER;
        case BufferType::Index:
            return GL_ELEMENT_ARRAY_BUFFER;
        }

        return 0;
    }

    GLBuffer::GLBuffer(BufferType bType, size_t size, size_t byteSize, bool isStatic) :
        m_GLType{ GetGLBufferType(bType) }, m_Size{ size }, m_ByteSize{ byteSize }, m_IsStatic{ isStatic }
    {
        GLCall(glGenBuffers(1, &m_Handle));
        OSE_ASSERT(m_Handle, "Could not create buffer");

        Bind();
        WriteData(nullptr);
    }

    GLBuffer::~GLBuffer()
    {
        Dispose();
    }

    void GLBuffer::Bind() const
    {
        GLCall(glBindBuffer(m_GLType, m_Handle));
    }

    void GLBuffer::Write(const byte* data, size_t length, size_t offset, bool discardAll) const
    {
        if (offset == 0 && length == m_ByteSize)
            WriteData(data);
        else
        {
            if(discardAll)
                WriteData(nullptr);

            if (offset + length < m_ByteSize)
                WriteSubData(data, length, offset);
        }
    }

    void GLBuffer::WriteData(const byte* data) const
    {
        GLCall(glBufferData(m_GLType, m_ByteSize, data, m_IsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
    }

    void GLBuffer::WriteSubData(const byte* data, size_t length, size_t offset) const
    {
        GLCall(glBufferSubData(m_GLType, offset, length, data));
    }

    void GLBuffer::Dispose()
    {
        if (m_Handle)
        {
            glDeleteBuffers(1, &m_Handle);
            m_Handle = 0;
        }
    }
}