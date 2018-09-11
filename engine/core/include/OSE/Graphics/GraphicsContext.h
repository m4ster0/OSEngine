#pragma once

#include "OSE/Graphics/ResourceID.h"
#include "OSE/Graphics/ResourceCommand.h"

#include <vector>

namespace OSE {

    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;
        virtual bool IsValid() = 0;

        virtual ResourceID CreateSwapChain(void* windowHandle) = 0;
        virtual void DestroySwapChain(ResourceID handle) = 0;

        virtual bool MakeCurrent(ResourceID handle) = 0;
        virtual bool Present(ResourceID handle) = 0;

        virtual void HandleDispose(ResourceID rid) = 0;

        void HandleProgramCommand(const ProgramCommand& cmd);
        void HandleVertexLayoutCommand(const VertexLayoutCommand& cmd);

    protected:
        GraphicsContext() = default;

        ResourceID m_ActiveSwapChain;

        virtual void CreateProgram() = 0;
        virtual void UpdateProgram(const std::vector<ShaderDescriptor>& shaderDescriptors) = 0;

        virtual void CreateLayout() = 0;
        virtual void UpdateLayout(const std::vector<VertexAttributeDescriptor>& attributeDescriptors) = 0;
    };

}
