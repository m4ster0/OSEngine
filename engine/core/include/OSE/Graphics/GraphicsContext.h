#pragma once

#include "OSE/Graphics/ResourceID.h"
#include "OSE/Graphics/GraphicsResourceDescriptor.h"

#include "OSE/Events/Signal.h"
#include "OSE/TypeDefs.h"

#include <vector>

namespace OSE {

    class GraphicsContext
    {
        friend class GraphicsResourceProxy;
        friend class GraphicsRenderer;

        Signal<void()> OnDestroyed;
    public:
        virtual ~GraphicsContext()
        {
            OnDestroyed.Invoke();
        }

        virtual bool IsValid() = 0;

        virtual SwapChainHandle CreateSwapChain(void* windowHandle) = 0;
        virtual bool MakeCurrent(SwapChainHandle handle) = 0;
        virtual bool Present(SwapChainHandle handle) = 0;
        virtual void DestroySwapChain(SwapChainHandle handle) = 0;

        virtual ProgramHandle Create(const std::vector<ShaderDescriptor>& shaderDescriptors) = 0;
        virtual void Dispose(ProgramHandle handle) = 0;

        virtual VertexLayoutHandle Create(const std::vector<VertexAttributeDescriptor>& attributeDescriptors) = 0;
        virtual void Dispose(VertexLayoutHandle handle) = 0;

        virtual BufferHandle Create(BufferDescriptor::Type type, const BufferDescriptor& desc, BufferDataDescriptor* dataDesc) = 0;
        virtual void Dispose(BufferHandle handle) = 0;

        virtual void Terminate() = 0;

        //create Buffer
        //create ImageBuffer

        //draw
        //drawIndexed
        //copy to buffer

    protected:
        GraphicsContext() = default;

        SwapChainHandle m_ActiveSwapChain;

        //todo move this functionality to derived classes ideally preserving templating
        template<ResourceType RT>
        ResourceID<RT> GenerateRID()
        {
            static size_t counter{ 0 };
            return ResourceID<RT>{ ++counter };
        }
    };

}
