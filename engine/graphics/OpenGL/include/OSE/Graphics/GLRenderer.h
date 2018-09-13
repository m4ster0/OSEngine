#pragma once

#include <OSE/Graphics/GraphicsRenderer.h>
#include <OSE/TypeDefs.h>

#include "OSE/Graphics/GLContext.h"

#include <memory>

namespace OSE {
    class GLRenderer: public GraphicsRenderer
    {
        friend class GLDevice;

        //state cache
        const GLContext* m_Context;
        GLRenderer(const GLContext* context);

        //void OnContextLoss();
    public:
        ~GLRenderer();

        void BindProgram(ProgramHandle handle) override;
        //uniforms binding todo

        void GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer) override;
        void GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer, BufferHandle indexBuffer) override;

        void Draw(VertexLayoutHandle layout, RenderPrimitive primitive,
            BufferHandle vertexBuffer, BufferHandle indexBuffer,
            size_t vertexCount = 0, size_t startVertex = 0) override;

        void DrawIndexed(VertexLayoutHandle layout, RenderPrimitive primitive,
            BufferHandle vertexBuffer, BufferHandle indexBuffer,
            size_t indexCount = 0, size_t startIndex = 0) override;

        void UpdateBuffer(BufferHandle handle, BufferDescriptor::Type type, const BufferDataDescriptor& data) override;
    };
}