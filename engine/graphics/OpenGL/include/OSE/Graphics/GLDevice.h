#pragma once

#include <OSE/Graphics/GraphicsDevice.h>

namespace OSE {

    class GLDevice : public GraphicsDevice
    {
    protected:
        virtual std::unique_ptr<GraphicsContext> CreateContextInternal() override;
        virtual GraphicsAPI GetAPI() override;
    };

}
