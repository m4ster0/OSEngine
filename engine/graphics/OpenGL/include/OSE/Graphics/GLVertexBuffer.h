#pragma once
#include "OSE/Graphics/GLBuffer.h"

#include <OSE/Graphics/Resource.h>

namespace OSE {
    class GLVertexBuffer : public GLBuffer<float>, public Resource<GLVertexBuffer>
    {
    public:
        GLVertexBuffer(size_t size, bool isStatic = true);
        ~GLVertexBuffer();

        void WriteData(const byte* data) override;
        void WriteSubData(const byte* data, size_t length, size_t offset) override;

        void Dispose() override;
    };
}