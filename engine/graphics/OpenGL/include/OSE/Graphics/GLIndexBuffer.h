#pragma once

#include "OSE/Graphics/GLBuffer.h"

#include <OSE/TypeDefs.h>

namespace OSE {
    class GLIndexBuffer : public GLBuffer
    {
    public:
        GLIndexBuffer(size_t size, bool isStatic = true);
        ~GLIndexBuffer();

        GLIndexBuffer(const GLIndexBuffer&) = delete;
        GLIndexBuffer& operator=(const GLIndexBuffer&) = delete;

        GLIndexBuffer(GLIndexBuffer&&) = delete;
        GLIndexBuffer& operator=(GLIndexBuffer&&) = delete;

        void Write(const byte* data) override;

        void Dispose() override;
    };
}