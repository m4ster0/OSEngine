#pragma once

#include "OSE/Graphics/GLResource.h"

#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/TypeDefs.h>

#include <vector>

namespace OSE {
    class GLBuffer: public GLResource
    {
        uint m_Handle{ 0 };

        uint m_GLType;
        size_t m_Size{ 0 };
        size_t m_ByteSize{ 0 };
        bool m_IsStatic{ true };

        void WriteData(const byte* data) const;
        void WriteSubData(const byte* data, size_t length, size_t offset) const;
    public:
        GLBuffer(int32 id, BufferType bType, size_t size, size_t byteSize, bool isStatic);

        GLBuffer(GLBuffer&&) = delete;
        GLBuffer& operator=(GLBuffer&&) = delete;

        ~GLBuffer();

        void Bind() const;
        void Write(const byte* data, size_t length, size_t offset, bool discardAll = false) const;

        void Dispose() override;

        inline size_t GetSize() const { return m_Size; }
        inline uint GetHandle() const { return m_Handle; }
    };
}