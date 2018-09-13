#pragma once

#include "OSE/Graphics/GraphicsContext.h"
#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"

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
        virtual void BindProgram(ProgramHandle handle) = 0;
        //uniforms binding todo

        virtual void GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer) = 0;
        virtual void GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer, BufferHandle indexBuffer) = 0;

        virtual void Draw(VertexLayoutHandle layout, RenderPrimitive primitive,
                        BufferHandle vertexBuffer, BufferHandle indexBuffer,
                        size_t vertexCount = 0, size_t startVertex = 0) = 0;

        virtual void DrawIndexed(VertexLayoutHandle layout, RenderPrimitive primitive,
                                BufferHandle vertexBuffer, BufferHandle indexBuffer,
                                size_t indexCount = 0, size_t startIndex = 0) = 0;

        virtual void UpdateBuffer(BufferHandle handle, BufferDescriptor::Type type, const BufferDataDescriptor& data) = 0;
    };

}