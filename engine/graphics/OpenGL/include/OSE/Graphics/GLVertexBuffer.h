#pragma once

#include "OSE/Graphics/GLBuffer.h"

#include <OSE/TypeDefs.h>
#include <vector>

namespace OSE {
    class GLVertexBuffer : public GLBuffer
    {
    public:
        GLVertexBuffer(size_t size, size_t vertexByteSize, bool isStatic = true);
        ~GLVertexBuffer();

        GLVertexBuffer(const GLVertexBuffer&) = delete;
        GLVertexBuffer& operator=(const GLVertexBuffer&) = delete;

        GLVertexBuffer(GLVertexBuffer&&) = delete;
        GLVertexBuffer& operator=(GLVertexBuffer&&) = delete;

        void Write(const byte* data) override;
        void Dispose() override;
    };
}