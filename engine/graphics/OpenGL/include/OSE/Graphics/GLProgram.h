#pragma once

#include "OSE/Graphics/GLResource.h"

#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/TypeDefs.h>

#include <memory>
#include <string>
#include <vector>

namespace OSE {

    class GLProgram : public GLResource
    {
        uint m_Handle{ 0 };

    public:
        static GLProgram* Create(const std::vector<ShaderDescriptor>& descs);

        GLProgram();

        GLProgram(GLProgram&&) = delete;
        GLProgram& operator=(GLProgram&&) = delete;

        ~GLProgram();

        void Bind() const;
        uint GetAttributeLocation(const std::string& name) const;
        uint GetUniformLocation(const std::string& name) const;

        void Dispose() override;

    };
}