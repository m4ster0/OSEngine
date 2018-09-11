#pragma once

#include <OSE/TypeDefs.h>

#include <vector>

namespace OSE {
    template<typename T>
    class GLBuffer
    {
    protected:
        uint m_Handle{ 0 };

        size_t m_Size{ 0 };
        size_t m_ByteSize{ 0 };
        bool m_IsStatic{ true };

        virtual void WriteData(const byte* data) = 0;
        virtual void WriteSubData(const byte* data, size_t length, size_t offset) = 0;
    public:
        GLBuffer(size_t size, bool isStatic) :
            m_Size{ size }, m_ByteSize{ size * sizeof(T) }, m_IsStatic{ isStatic }
        {
        }

        GLBuffer(const GLBuffer&) = delete;
        GLBuffer& operator=(const GLBuffer&) = delete;

        GLBuffer(GLBuffer&&) = delete;
        GLBuffer& operator=(GLBuffer&&) = delete;

        virtual ~GLBuffer() = default;

        void Write(const byte* data, size_t length, size_t offset, bool discardAll)
        {
            if (offset == 0 && length == m_ByteSize)
                WriteData(data);
            else
            {
                if (discardAll)
                    WriteData(nullptr);

                if(offset + length < m_ByteSize)
                    WriteSubData(data, length, offset);
            }
        }

        void Write(const T* data, size_t length, size_t offset = 0, bool discardAll = false)
        {
            Write(reinterpret_cast<const byte*>(data), length * sizeof(T), offset * sizeof(T), discardAll);
        }

        void Write(const std::vector<T>& data, size_t offset = 0, bool discardAll = false)
        {
            Write(&data[0], data.size(), offset, discardAll);
        }

        inline size_t GetSize() const { return m_Size; }
        inline uint GetHandle() const { return m_Handle; }
    };
}