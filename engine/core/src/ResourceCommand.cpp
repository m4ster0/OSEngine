#include "OSE/Graphics/ResourceCommand.h"
#include "OSE/Graphics/ResourceCommandDescriptor.h"
#include "OSE/Graphics/GraphicsContext.h"

namespace OSE {

    using AttrType = VertexAttributeDescriptor::Type;

    std::unordered_map<AttrType, std::string> VertexAttributeDescriptor::TypeName = {
        {AttrType::Position     , "aPosition"},
        {AttrType::Normal       , "aNormal"},
        {AttrType::Color        , "aColor"},
        {AttrType::TexCoord0    , "aTexCoord0"},
        {AttrType::TexCoord1    , "aTexCoord1"}
    };

    //******  Dispose Commands *******//
    void DisposeCommand::Process(GraphicsContext& context)
    {
        context.HandleDispose(rid);
    }

    //******  Program Commands *******//
    ResourceID ProgramCommand::GenerateRID()
    {
        return ResourceID{ ++RIDCounter<ResourceType::Program>::Counter, ResourceType::Program };
    }

    void ProgramCommand::Process(GraphicsContext& context)
    {
        context.HandleProgramCommand(*this);
    }

    //******  Vertex Layout Commands *******//
    ResourceID VertexLayoutCommand::GenerateRID()
    {
        return ResourceID{ ++RIDCounter<ResourceType::VertexLayout>::Counter, ResourceType::VertexLayout };
    }

    void VertexLayoutCommand::Process(GraphicsContext& context)
    {
        context.HandleVertexLayoutCommand(*this);
    }
}