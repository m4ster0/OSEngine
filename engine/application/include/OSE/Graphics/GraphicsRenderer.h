#pragma once

#include "OSE/Graphics/GraphicsResourceDescriptor.h"
#include "OSE/Graphics/ResourceID.h"
#include "OSE/Graphics/Color.h"

#include "OSE/TypeDefs.h"
#include "OSE/EnumClassFlags.h"

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

    enum class GraphicsBufferMode: byte
    {
        Color = 0x01,
        Depth = 0x02,
        Stencil = 0x04
    };

    enum class GraphicsBlendFactor
    {
        Zero,
        One,
        SrcAlpha,
        DstAlpha,
        OneMinusSrcAlpha,
        OneMinusDstAlpha
    };

    enum class GraphicsTestFunction
    {
        Never,
        Always,
        Less, LessEqual,
        Greater, GreaterEqual,
        Equal, NotEqual
    };

    class GraphicsRenderer
    {
    public:
        virtual ~GraphicsRenderer() = default;

        virtual void SetBlend(bool enabled) = 0;
        virtual void SetBlendFunc(GraphicsBlendFactor srcFactor, GraphicsBlendFactor dstFactor) = 0;
        virtual void SetDepthTest(bool enabled) = 0;
        virtual void SetDepthTestFunc(GraphicsTestFunction func) = 0;
        virtual void SetStencilTest(bool enabled) = 0;
        virtual void SetStencilTestFunc(GraphicsTestFunction func) = 0;
        virtual void SetCullFace(bool enabled) = 0;

        virtual void SetViewport(uint x, uint y, uint width, uint height) = 0;
        virtual void SetClearColor(const Color& color) = 0;
        virtual void SetClearColor(float r, float g, float b, float a) = 0;
        virtual void Clear(GraphicsBufferMode modes) = 0;

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

ENABLE_BITMASK_OPERATORS(OSE::GraphicsBufferMode);