#pragma once

#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"

namespace OSE {

    template<ResourceType RT>
    struct GraphicsResource
    {
        ResourceID<RT> rid;

        GraphicsResource() = default;

        GraphicsResource(const GraphicsResource&) = delete;
        GraphicsResource& operator=(const GraphicsResource&) = delete;

        GraphicsResource(GraphicsResource&&) = delete;
        GraphicsResource& operator=(GraphicsResource&&) = delete;

        virtual ~GraphicsResource() = default;

        virtual void Dispose() = 0;
    };

}