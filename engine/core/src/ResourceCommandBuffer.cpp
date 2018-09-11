#include "OSE/Graphics/ResourceCommandBuffer.h"

namespace OSE {
    ResourceCommandBuffer::ResourceCommandBuffer(const std::weak_ptr<GraphicsContext>& context):
        m_Context{ context }
    {

    }

    void ResourceCommandBuffer::Clear()
    {
        m_Commands.clear();
    }

    void ResourceCommandBuffer::Submit()
    {
        std::shared_ptr<GraphicsContext> context = m_Context.lock();
        if (context)
        {
            for (const auto& command : m_Commands)
                command->Process(*context);
        }

        Clear();
    }
}