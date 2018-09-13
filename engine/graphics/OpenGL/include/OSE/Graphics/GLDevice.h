#pragma once

#include <OSE/Graphics/GraphicsDevice.h>

namespace OSE {

    class GLDevice : public GraphicsDevice
    {
    public:
        std::unique_ptr<GraphicsRenderer> CreateRenderer() override;
    protected:
        virtual void InitializeInternal() override;
        virtual GraphicsAPI GetAPI() override;
    };

}
