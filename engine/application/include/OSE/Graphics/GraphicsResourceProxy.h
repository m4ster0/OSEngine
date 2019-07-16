#pragma once

#include "OSE/Graphics/GraphicsResourceDescriptor.h"
#include "OSE/Graphics/GraphicsProgramUniform.h"
#include "OSE/Graphics/ResourceID.h"
#include "OSE/Resources/Image.h"

#include <utility>

namespace OSE {

    //main thread access to graphics resources
    class GraphicsResourceProxy
    {
    public:
        virtual ~GraphicsResourceProxy() = default;

        virtual ProgramHandle CreateProgram(const std::vector<ShaderDescriptor>& shaderDescriptors) = 0;
        virtual void DisposeProgram(ProgramHandle handle) = 0;

        template<typename T> const ProgramUniform<T>* GetProgramUniform(ProgramHandle handle, const std::string& name) const;
        template<typename T> const ProgramUniformV<T>* GetProgramUniformV(ProgramHandle handle, const std::string& name) const;

        virtual BufferHandle CreateBuffer(BufferDescriptor::Type type, const BufferDescriptor& desc, const BufferDataDescriptor* dataDesc = nullptr) = 0;
        virtual void DisposeBuffer(BufferHandle handle) = 0;

        virtual VertexLayoutHandle CreateVertexLayout(const std::vector<VertexAttributeDescriptor>& attributeDescriptors) = 0;
        virtual void DisposeVertexLayout(VertexLayoutHandle handle) = 0;

        virtual void GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer) = 0;
        virtual void GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer, BufferHandle indexBuffer) = 0;

        virtual TextureHandle CreateTexture(const TextureDescriptor& desc, const Image* image = nullptr) = 0;
        virtual void DisposeTexture(TextureHandle handle) = 0;
    protected:
        virtual const ProgramUniformBase* GetUniform(ProgramHandle handle, const std::string& name) const = 0;
    };

    template<typename T>
    const ProgramUniform<T>* GraphicsResourceProxy::GetProgramUniform(ProgramHandle handle, const std::string& name) const
    {
        const ProgramUniformBase* uniform = GetUniform(handle, name);
        return dynamic_cast<const ProgramUniform<T>*>(uniform);
    }

    template<typename T>
    const ProgramUniformV<T>* GraphicsResourceProxy::GetProgramUniformV(ProgramHandle handle, const std::string& name) const
    {
        const ProgramUniformBase* uniform = GetUniform(handle, name);
        return dynamic_cast<const ProgramUniformV<T>*>(uniform);
    }
}