#pragma once

#include <OSE/Graphics/GraphicsResource.h>
#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/TypeDefs.h>

#include <vector>

namespace OSE {
    class GLBuffer: public GraphicsResource<ResourceType::Buffer>
    {
    protected:
        uint m_Handle{ 0 };

        uint m_GLType;
        size_t m_Size{ 0 };
        size_t m_ByteSize{ 0 };
        bool m_IsStatic{ true };

        void WriteData(const byte* data) const;
        void WriteSubData(const byte* data, size_t length, size_t offset) const;
    public:
        static void Unbind(const GLBuffer& buffer);

        GLBuffer(BufferType bType, size_t size, size_t byteSize, bool isStatic);
        ~GLBuffer();

        void Bind() const;
        void Write(const byte* data, size_t length, size_t offset, bool discardAll = false) const;

        void Dispose() override;

        inline size_t GetSize() const { return m_Size; }
        inline uint GetHandle() const { return m_Handle; }
    };
}