#pragma once

#include <OSE/Graphics/GraphicsContext.h>
#include <OSE/TypeDefs.h>

#include "OSE/Graphics/GLProgram.h"
#include "OSE/Graphics/GLBuffer.h"
#include "OSE/Graphics/GLVertexArray.h"

#include <vector>
#include <memory>

namespace OSE {

    class GLContext : public GraphicsContext
    {
        template<class R>
        class Resources
        {
            using RUPtr = std::unique_ptr<R>;

            std::vector<RUPtr> m_Data;
            int32 m_MaxSize;
            int32 m_NextIndex{ 0 };

        public:
            Resources(int32 maxSize);

            R* Retrieve(int32 index) const
            {
                if (index >= 0 && index < m_MaxSize)
                    return m_Data[index].get();

                return nullptr;
            }

            bool HasNext() const;
            int32 PutNext(RUPtr resource);

            void Remove(int32 index);

            void Clear();
        };

        Resources<GLProgram> m_ProgramResources;
        Resources<GLBuffer> m_BufferResources;
        Resources<GLVertexArray> m_VertexArrayResources;

    public:
        virtual ~GLContext() = default;

        virtual ProgramHandle Create(const std::vector<ShaderDescriptor>& shaderDescriptors) override;
        inline GLProgram* GetProgram(ProgramHandle handle) const { return m_ProgramResources.Retrieve(handle.GetID()); }
        virtual void Dispose(ProgramHandle handle) override;

        virtual BufferHandle Create(BufferType type, const BufferDescriptor& desc, BufferDataDescriptor* dataDesc) override;
        inline GLBuffer* GetBuffer(BufferHandle handle) const { return m_BufferResources.Retrieve(handle.GetID()); }
        virtual void Dispose(BufferHandle handle) override;

        virtual VertexLayoutHandle Create(const std::vector<VertexAttributeDescriptor>& attributeDescriptors) override;
        inline GLVertexArray* GetVertexArray(VertexLayoutHandle handle) const { return m_VertexArrayResources.Retrieve(handle.GetID()); }
        virtual void Dispose(VertexLayoutHandle handle) override;

        virtual void Terminate() override;

    protected:
        GLContext();
    };
}