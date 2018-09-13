#include "OSE/Graphics/GraphicsResourceProxy.h"

namespace OSE {

    GraphicsResourceProxy::GraphicsResourceProxy(GraphicsContext* context):
        m_Context{ context }
    {
        if (m_Context)
            m_Context->OnDestroyed.Add<GraphicsResourceProxy, &GraphicsResourceProxy::OnContextLoss>(this);
    }

    GraphicsResourceProxy::~GraphicsResourceProxy()
    {
        if (m_Context)
            OnContextLoss();
    }

    ProgramHandle GraphicsResourceProxy::CreateProgram(const std::vector<ShaderDescriptor>& shaderDescriptors)
    {
        if (m_Context)
            return m_Context->Create(shaderDescriptors);

        return ProgramHandle::Invalid;
    }

    VertexLayoutHandle GraphicsResourceProxy::CreateVertexLayout(const std::vector<VertexAttributeDescriptor>& attributeDescriptors)
    {
        if (m_Context)
            return m_Context->Create(attributeDescriptors);

        return VertexLayoutHandle::Invalid;
    }

    BufferHandle GraphicsResourceProxy::CreateBuffer(BufferDescriptor::Type type, const BufferDescriptor& desc, BufferDataDescriptor* dataDesc)
    {
        if (m_Context)
            return m_Context->Create(type, desc, dataDesc);

        return BufferHandle::Invalid;
    }

    void GraphicsResourceProxy::OnContextLoss()
    {
        m_Context->OnDestroyed.Remove<GraphicsResourceProxy, &GraphicsResourceProxy::OnContextLoss>(this);
        m_Context = nullptr;
    }
}