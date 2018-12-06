#pragma once

#include <OSE/Graphics/GraphicsRenderer.h>
#include <OSE/TypeDefs.h>

#include <memory>

namespace OSE {
    class GLContext;

    class GLRenderer: public GraphicsRenderer
    {
        //state cache
        GLContext* m_Context;

    public:
        GLRenderer(GLContext* context);

        //state setters
        void SetViewport(uint x, uint y, uint width, uint height);
        void SetClearColor(const Color& color);
        void SetClearColor(float r, float g, float b, float a);

        void SetBlend(bool enabled);
        void SetBlendFunc(GraphicsBlendFactor srcFactor, GraphicsBlendFactor dstFactor);
        void SetDepthTest(bool enabled);
        void SetDepthTestFunc(GraphicsTestFunction func);
        void SetStencilTest(bool enabled);
        void SetStencilTestFunc(GraphicsTestFunction func);
        void SetCullFace(bool enabled);

        void BindProgram(ProgramHandle handle) override;
        void BindTexture(TextureHandle handle, uint slot = 0) override;

        //actions
        void Clear(GraphicsBufferMode modes);
        void Draw(VertexLayoutHandle layout, RenderPrimitive primitive,
            BufferHandle vertexBuffer,
            size_t vertexCount = 0, size_t startVertex = 0) override;

        void DrawIndexed(VertexLayoutHandle layout, RenderPrimitive primitive,
            BufferHandle vertexBuffer, BufferHandle indexBuffer,
            size_t indexCount = 0, size_t startIndex = 0) override;

        void UpdateBuffer(BufferHandle handle, BufferDescriptor::Type type, const BufferDataDescriptor& data) override;
    };
}