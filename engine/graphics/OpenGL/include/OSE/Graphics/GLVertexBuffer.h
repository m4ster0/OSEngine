#pragma once

#include "OSE/Graphics/GLBuffer.h"

#include <OSE/TypeDefs.h>

namespace OSE {
    class GLVertexBuffer : public GLBuffer
    {
    public:
        static void Clear();

        GLVertexBuffer(size_t size, size_t vertexByteSize, bool isStatic = true);

        GLVertexBuffer(const GLVertexBuffer&) = delete;
        GLVertexBuffer& operator=(const GLVertexBuffer&) = delete;

        GLVertexBuffer(GLVertexBuffer&&) = delete;
        GLVertexBuffer& operator=(GLVertexBuffer&&) = delete;

        void Write(const byte* data) override;
        void Bind() override;

        void Dispose() override;
    };
}