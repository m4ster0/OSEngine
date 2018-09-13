#pragma once

#include "OSE/Graphics/GraphicsContext.h"
#include "OSE/Graphics/ResourceID.h"

#include <utility>

namespace OSE {

    //main thread access to graphics resources
    class GraphicsResourceProxy
    {
        friend class GraphicsDevice;

        GraphicsContext* m_Context;
        GraphicsResourceProxy(GraphicsContext* context);

        void OnContextLoss();

    public:
        ~GraphicsResourceProxy();

        ProgramHandle CreateProgram(const std::vector<ShaderDescriptor>& shaderDescriptors);
        BufferHandle CreateBuffer(BufferDescriptor::Type type, const BufferDescriptor& desc, BufferDataDescriptor* dataDesc = nullptr);
        VertexLayoutHandle CreateVertexLayout(const std::vector<VertexAttributeDescriptor>& attributeDescriptors);

        inline bool IsValid() const { return m_Context != nullptr; }

        template<ResourceType RT>
        void Dispose(ResourceID<RT> rid);
    };

    template<ResourceType RT>
    void GraphicsResourceProxy::Dispose(ResourceID<RT> rid)
    {
        if (m_Context)
            m_Context->Dispose(rid);
    }
}