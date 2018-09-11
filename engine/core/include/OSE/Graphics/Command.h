#pragma once

#include "OSE/Graphics/ResourceID.h"

namespace OSE {
    struct Command
    {
        friend class GraphicsContext;

        virtual ~Command() = default;
    protected:
        ResourceID rid;

        virtual void Process(GraphicsContext& context) = 0;
    };

    struct ResourceCommand: public Command
    {
        friend class ResourceCommandBuffer;

        virtual ~ResourceCommand() = default;
    };
}