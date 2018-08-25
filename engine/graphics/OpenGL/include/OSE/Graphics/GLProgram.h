#pragma once

#include "OSE/Graphics/GLShader.h"

#include <OSE/Graphics/Resource.h>
#include <OSE/System/FileSystem.h>
#include <OSE/TypeDefs.h>

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace OSE {

    class GLProgram: public Resource<GLProgram>
    {
        uint m_Handle{ 0 };
        bool m_Init{ false };
    public:
        class Builder
        {
        protected:
            std::vector<std::unique_ptr<GLShader>> m_Shaders;
            std::unordered_map<std::string, uint> m_AttribBinds;
            
            bool HasShader(GLShader::Type type);
        public:
            Builder();

            virtual Builder& AddShader(GLShader::Type type, const std::string& source);
            virtual Builder& BindAttribute(uint location, const std::string& name);
            std::unique_ptr<GLProgram> Create();
        };

        class SingleSrcBuilder: public Builder
        {
            std::string m_Source;

        public:
            SingleSrcBuilder(const std::string& source);
            SingleSrcBuilder(const FileSystem& fileSystem, const std::string& devicePath);
            SingleSrcBuilder(const FileSystem& fileSystem, const std::string& device, const std::string& path);

            virtual Builder& AddShader(GLShader::Type type, const std::string& typeTag) override;
        };

        GLProgram();
        GLProgram(const GLProgram& other) = delete;
        GLProgram(GLProgram&& other) = delete;

        GLProgram& operator=(const GLProgram& other) = delete;
        GLProgram& operator=(GLProgram&& other) = delete;

        ~GLProgram();

        void AttachShader(const GLShader& shader);
        void BindAttribute(uint location, const std::string& name);
        bool Link();

        void Begin();
        void End();

        uint GetAttributeLocation(const std::string& name);

        void Dispose();        
    };
}