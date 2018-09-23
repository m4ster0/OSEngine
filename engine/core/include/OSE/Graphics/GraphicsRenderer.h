#pragma once

#include "OSE/Graphics/GraphicsResourceDescriptor.h"
#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"
#include "OSE/Math/Vector.h"
#include "OSE/Math/Matrix.h"

#include <string>

namespace OSE {

    enum class RenderPrimitive : byte
    {
        Points,
        Lines, LineStrip,
        Triangles, TriangleStrip, TriangleFan
    };

    class GraphicsRenderer
    {
    public:
        virtual ~GraphicsRenderer() = default;

        virtual void BindProgram(ProgramHandle handle) = 0;
        virtual void BindTexture(TextureHandle handle, uint slot = 0) = 0;

        virtual void Draw(VertexLayoutHandle layout, RenderPrimitive primitive,
                        BufferHandle vertexBuffer,
                        size_t vertexCount = 0, size_t startVertex = 0) = 0;

        virtual void DrawIndexed(VertexLayoutHandle layout, RenderPrimitive primitive,
                                BufferHandle vertexBuffer, BufferHandle indexBuffer,
                                size_t indexCount = 0, size_t startIndex = 0) = 0;

        virtual void UpdateBuffer(BufferHandle handle, BufferDescriptor::Type type, const BufferDataDescriptor& data) = 0;
    };

}