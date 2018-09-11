#pragma once

#include "OSE/Graphics/GraphicsContext.h"
#include "OSE/Graphics/ResourceID.h"
#include "OSE/Graphics/ResourceCommand.h"

#include "OSE/TypeDefs.h"

#include <type_traits>
#include <utility>
#include <vector>
#include <memory>

namespace OSE {

    class ResourceCommandBuffer
    {
        friend class GraphicsDevice;

        std::weak_ptr<GraphicsContext> m_Context;
        std::vector<std::unique_ptr<ResourceCommand>> m_Commands;

        ResourceCommandBuffer(const std::weak_ptr<GraphicsContext>& context);

        template<typename T>
        T* AddCommandInternal(ResourceID rid)
        {
            static_assert(std::is_base_of<ResourceCommand, T>::value, "Command must have base type of ResourceCommand");

            std::unique_ptr<T> command = std::make_unique<T>();
            T* commandRaw = command.get();
            ResourceCommand* resCommand = static_cast<ResourceCommand*>(commandRaw);
            resCommand->rid = rid;

            m_Commands.push_back(std::move(command));

            return commandRaw;
        }

    public:
        template<typename T>
        T* AddUpdateCommand(ResourceID rid)
        {
            return AddCommandInternal<T>(rid);
        }

        template<typename T>
        std::pair<ResourceID, T*> AddCreateCommand()
        {
            ResourceID rid = T::GenerateRID();
            T* command = AddCommandInternal<T>(rid);
            if (command != nullptr)
                return std::make_pair(rid, command);

            return std::make_pair(ResourceID::Invalid, nullptr);
        }

        template<>
        std::pair<ResourceID, DisposeCommand*> AddCreateCommand<DisposeCommand>() = delete;

        void Clear();
        void Submit(); //submit commands to context; must be called from rendering thread
    };

}