#pragma once

#include <OSE/Graphics/Resource.h>
#include <OSE/TypeDefs.h>

namespace OSE {
    class GLBuffer : public Resource<GLBuffer>
    {
    protected:
        uint m_Handle{ 0 };

        size_t m_Size{ 0 };
        size_t m_ByteSize{ 0 };
        bool m_IsStatic{ true };

    public:
        GLBuffer(size_t size, size_t elementByteSize, bool isStatic) :
            m_Size{ size }, m_ByteSize{ size * elementByteSize }, m_IsStatic{ isStatic }
        {
        }

        GLBuffer(const GLBuffer&) = delete;
        GLBuffer& operator=(const GLBuffer&) = delete;

        GLBuffer(GLBuffer&&) = delete;
        GLBuffer& operator=(GLBuffer&&) = delete;

        virtual ~GLBuffer() = default;

        virtual void Write(const byte* data) = 0;
        virtual void Bind() = 0;

        inline size_t GetSize() const { return m_Size; }
    };
}