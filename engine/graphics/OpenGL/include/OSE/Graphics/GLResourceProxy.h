#pragma once

#include "OSE/Graphics/GLContext.h"

#include <OSE/Graphics/GraphicsResourceProxy.h>

namespace OSE {

    class GLResourceProxy : public GraphicsResourceProxy
    {
        GLContext* m_Context;
    public:
        GLResourceProxy(GLContext* context);

        ProgramHandle CreateProgram(const std::vector<ShaderDescriptor>& shaderDescriptors) override;
        void DisposeProgram(ProgramHandle handle) override;

        BufferHandle CreateBuffer(BufferDescriptor::Type type, const BufferDescriptor& desc, const BufferDataDescriptor* dataDesc = nullptr) override;
        void DisposeBuffer(BufferHandle handle) override;

        VertexLayoutHandle CreateVertexLayout(const std::vector<VertexAttributeDescriptor>& attributeDescriptors) override;
        void DisposeVertexLayout(VertexLayoutHandle handle) override;

        void GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer) override;
        void GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer, BufferHandle indexBuffer) override;

        TextureHandle CreateTexture(const TextureDescriptor& desc, const Image* image = nullptr) override;
        void DisposeTexture(TextureHandle handle) override;
    };

}