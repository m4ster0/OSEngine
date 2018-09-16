#pragma once

#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"

namespace OSE {

    struct GLResource
    {
        int32 rid{ 0 };

        GLResource() = default;
        virtual ~GLResource() = default;

        virtual void Dispose() = 0;
    };

}