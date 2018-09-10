#pragma once

#include "OSE/Graphics/GLBuffer.h"

#include <OSE/Graphics/Resource.h>

namespace OSE {
    class GLIndexBuffer : public GLBuffer<uint16>, public Resource<GLIndexBuffer>
    {
    public:
        GLIndexBuffer(size_t size, bool isStatic = true);
        ~GLIndexBuffer();

        void WriteData(const byte* data) override;
        void WriteSubData(const byte* data, size_t length, size_t offset) override;

        void Dispose() override;
    };
}