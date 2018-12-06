#pragma once

#include <OSE/Graphics/GraphicsRenderer.h>

namespace OSE {

    struct GLState
    {
        struct BlendFactors
        {
            GraphicsBlendFactor src{ GraphicsBlendFactor::One };
            GraphicsBlendFactor dst{ GraphicsBlendFactor::Zero };
        };

        bool blend{ false };
        BlendFactors blendFactors{ };
        bool depthTest{ false };
        GraphicsTestFunction depthTestFunc{ GraphicsTestFunction::Less };
        bool stencilTest{ false };
        GraphicsTestFunction stencilTestFunc{ GraphicsTestFunction::Always };
        bool cullFace{ false };

    };

}