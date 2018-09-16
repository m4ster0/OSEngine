#include "OSE/Graphics/GraphicsResourceDescriptor.h"

#include <functional>

namespace OSE {

    using AttrType = VertexAttributeDescriptor::Type;

    std::unordered_map<AttrType, std::string> VertexAttributeDescriptor::TypeName = {
        {AttrType::Position     , "aPosition"},
        {AttrType::Normal       , "aNormal"},
        {AttrType::Color        , "aColor"},
        {AttrType::TexCoord0    , "aTexCoord0"},
        {AttrType::TexCoord1    , "aTexCoord1"}
    };

    std::vector<ShaderDescriptor> shaderDescriptorsFromSources(const std::string& vertSrc, const std::string& fragSrc)
    {
        using ShaderT = ShaderDescriptor::Type;

        return { {ShaderT::Vertex, vertSrc}, {ShaderT::Fragment, fragSrc} };
    }

    std::vector<ShaderDescriptor> shaderDescriptorsFromSource(const std::string& singleSrc)
    {
        using ShaderT = ShaderDescriptor::Type;

        static std::unordered_map<ShaderT, std::string> names = {
            { ShaderT::Vertex, "vertex" },
            { ShaderT::Fragment, "fragment" }
        };

        std::function<ShaderDescriptor(ShaderT)> getShaderDesc = [&singleSrc](ShaderT type) -> ShaderDescriptor {
            static const std::string tag{ "%%" };

            std::string shaderTag{ tag + names[type] };
            std::string::size_type start{ singleSrc.find(shaderTag) };
            std::size_t startPos = start + shaderTag.length();

            std::string::size_type end{ 0 };
            if (start != std::string::npos && (end = singleSrc.find(shaderTag, startPos)))
                return { type, singleSrc.substr(startPos, end - startPos) };

            return { type, "" };
        };

        return { getShaderDesc(ShaderT::Vertex), getShaderDesc(ShaderT::Fragment) };
    }

}