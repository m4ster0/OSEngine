#pragma once

#include <OSE/TypeDefs.h>
#include <OSE/Graphics/GraphicsConfiguration.h>

#include "OSE/Graphics/ResourceStorage.h"
#include "OSE/Graphics/GLProgram.h"
#include "OSE/Graphics/GLBuffer.h"
#include "OSE/Graphics/GLVertexArray.h"
#include "OSE/Graphics/GLTexture.h"

#include "OSE/Graphics/GLResourceProxy.h"
#include "OSE/Graphics/GLRenderer.h"

#include <vector>
#include <memory>

namespace OSE {

    class GLContext
    {
        friend class GLResourceProxy;
        friend class GLRenderer;
    public:
        GLContext();

        GLContext(GLContext&&) = delete;
        GLContext& operator=(GLContext&&) = delete;

        virtual ~GLContext() = default;

        virtual SwapChainHandle CreateSwapChain(void* windowHandle) = 0;
        virtual bool MakeCurrent(SwapChainHandle handle) = 0;
        virtual bool Present(SwapChainHandle handle) = 0;
        virtual void DestroySwapChain(SwapChainHandle handle) = 0;

        virtual bool IsValid() = 0;
        virtual void Dispose();

        inline const GraphicsConfig& GetConfig() const { return m_CurrentConfig; }
        inline GLResourceProxy& GetResourceProxy() { return m_ResourceProxy; }
        inline GLRenderer& GetRenderer() { return m_Renderer; }
    protected:
        GraphicsConfig m_CurrentConfig{ };

        ResourceStorage<GLProgram> m_ProgramResources;
        ResourceStorage<GLBuffer> m_BufferResources;
        ResourceStorage<GLVertexArray> m_VertexArrayResources;
        ResourceStorage<GLTexture> m_TextureResources;

        ProgramHandle m_CurrentProgram;

        GLResourceProxy m_ResourceProxy;
        GLRenderer m_Renderer;
    };
}