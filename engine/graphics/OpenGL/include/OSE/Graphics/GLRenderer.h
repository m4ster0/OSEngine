#pragma once

#include <OSE/Graphics/GraphicsRenderer.h>
#include <OSE/TypeDefs.h>

#include "OSE/Graphics/GLContext.h"

#include <memory>

namespace OSE {
    class GLRenderer: public GraphicsRenderer
    {
        //state cache
        GLContext* m_Context;

    public:
        GLRenderer(GLContext* context);

        void BindProgram(ProgramHandle handle) override;
        void SetProgramUniform(const ProgramUniform& uniform, int value) override;
        void SetProgramUniform(const ProgramUniform& uniform, const int* values, size_t count) override;
        void SetProgramUniform(const ProgramUniform& uniform, float value) override;
        void SetProgramUniform(const ProgramUniform& uniform, const float* values, size_t count) override;

        void BindTexture(TextureHandle handle, uint slot = 0) override;

        void Draw(VertexLayoutHandle layout, RenderPrimitive primitive,
            BufferHandle vertexBuffer,
            size_t vertexCount = 0, size_t startVertex = 0) override;

        void DrawIndexed(VertexLayoutHandle layout, RenderPrimitive primitive,
            BufferHandle vertexBuffer, BufferHandle indexBuffer,
            size_t indexCount = 0, size_t startIndex = 0) override;

        void UpdateBuffer(BufferHandle handle, BufferDescriptor::Type type, const BufferDataDescriptor& data) override;
    };
}