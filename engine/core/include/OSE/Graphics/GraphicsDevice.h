#pragma once

#include "OSE/Graphics/GraphicsContext.h"
#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"

#include <memory>
#include <unordered_map>

namespace OSE {

    enum class GraphicsAPI
    {
        OPENGL,
        DIRECTX11
    };

    class GraphicsDevice
    {
        friend class Platform;

    public:
        virtual ~GraphicsDevice() = default;

        ResourceID CreateSwapChain(void* windowHandle);

        bool MakeCurrent(ResourceID handle);
        bool Present(ResourceID handle);

        void DestroySwapChain(ResourceID handle);

    protected:
        std::unique_ptr<GraphicsContext> m_ImmediateContext{ nullptr };

        virtual std::unique_ptr<GraphicsContext> CreateContextInternal() = 0;
        virtual GraphicsAPI GetAPI() = 0;

    private:
        bool Initialize();
        void Terminate();
    };

}
