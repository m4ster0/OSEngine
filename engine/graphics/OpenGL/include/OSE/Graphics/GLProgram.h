#pragma once

#include <OSE/Graphics/GraphicsResource.h>
#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/TypeDefs.h>

#include <memory>
#include <string>
#include <vector>

namespace OSE {

    class GLProgram : public GraphicsResource<ResourceType::Program>
    {
        uint m_Handle{ 0 };

    public:
        static std::unique_ptr<GLProgram> Create(const std::vector<ShaderDescriptor>& descs);

        GLProgram();
        ~GLProgram();

        void Bind() const;
        uint GetAttributeLocation(const std::string& name) const;
        uint GetUniformLocation(const std::string& name) const;

        //uniform setters
        //void SetUniform1(const std::string& name, int value) const;
        //void SetUniform1(const std::string& name, float value) const;

        void Dispose() override;

    };
}