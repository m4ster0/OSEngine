#pragma once

#include "OSE/Graphics/GLResource.h"
#include "OSE/Graphics/GLProgramUniform.h"

#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/TypeDefs.h>

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace OSE {

    class GLProgram : public GLResource
    {
        using UniformPtr = std::unique_ptr<ProgramUniform>;
        using UniformCache = std::unordered_map<std::string, UniformPtr>;

        uint m_Handle{ 0 };
        UniformCache m_Uniforms;

        //TODO add some defines for compilation
        void Preprocess();
        void Compile(const std::vector<ShaderDescriptor>& descs);
        void CreateUniformCache();

        std::unique_ptr<ProgramUniform> CreateUniform(const std::string& name, uint type, int size);
        int GetAttributeLocation(const std::string& name) const;
        int GetUniformLocation(const std::string& name) const;
    public:
        GLProgram(int32 id, const std::vector<ShaderDescriptor>& descs);

        GLProgram(GLProgram&&) = delete;
        GLProgram& operator=(GLProgram&&) = delete;

        ~GLProgram();

        void Bind() const;
        ProgramUniform* GetUniform(const std::string& name) const;
        inline size_t GetUniformCount() const { return m_Uniforms.size(); }

        void Dispose() override;

    };
}