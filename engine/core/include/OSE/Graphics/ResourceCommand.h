#pragma once

#include "OSE/Graphics/Command.h"
#include "OSE/Graphics/ResourceCommandDescriptor.h"

#include <string>
#include <vector>


namespace OSE {

    struct DisposeCommand : public ResourceCommand
    {
    protected:
        void Process(GraphicsContext& context) override;
    };

    struct ProgramCommand : public ResourceCommand
    {
        static ResourceID GenerateRID();

        std::vector<ShaderDescriptor> shaderDescriptors;
        //some defines and other compilation specific things
    protected:
        void Process(GraphicsContext& context) override;
    };

    struct VertexLayoutCommand : public ResourceCommand
    {
        static ResourceID GenerateRID();

        std::vector<VertexAttributeDescriptor> attributeDescriptors;

    protected:
        void Process(GraphicsContext& context) override;
    };

    //struct BufferCommand : public ResourceCommand
    //{
    //    std::unique_ptr<BufferDescriptor> descriptor{ nullptr };
    //    std::unique_ptr<BufferDataDescriptor> dataDescriptor{ nullptr };
    //};

    //struct ImageBufferCommand : public ResourceCommand
    //{
    //    //TODO
    //};
}