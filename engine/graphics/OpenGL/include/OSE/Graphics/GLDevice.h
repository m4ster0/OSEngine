#pragma once

#include <OSE/Graphics/GraphicsDevice.h>

namespace OSE {

    class GLDevice : public GraphicsDevice
    {
    protected:
        virtual void CreateContextInternal() override;
        virtual GraphicsAPI GetAPI() override;
    };

}
