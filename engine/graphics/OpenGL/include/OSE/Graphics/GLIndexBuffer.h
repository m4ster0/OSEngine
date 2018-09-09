#pragma once

#include "OSE/Graphics/GLBuffer.h"

#include <OSE/TypeDefs.h>

namespace OSE {
    class GLIndexBuffer : public GLBuffer
    {
    public:
        static void Clear();

        GLIndexBuffer(size_t size, bool isStatic = true);

        GLIndexBuffer(const GLIndexBuffer&) = delete;
        GLIndexBuffer& operator=(const GLIndexBuffer&) = delete;

        GLIndexBuffer(GLIndexBuffer&&) = delete;
        GLIndexBuffer& operator=(GLIndexBuffer&&) = delete;

        void Write(const byte* data) override;
        void Bind() override;

        void Dispose() override;
    };
}