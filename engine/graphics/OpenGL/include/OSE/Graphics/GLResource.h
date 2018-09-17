#pragma once

#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"

namespace OSE {

    struct GLResource
    {
        int32 rid;

        GLResource(int32 id) : rid{ id } {};
        virtual ~GLResource() = default;

        virtual void Dispose() = 0;
    };

}