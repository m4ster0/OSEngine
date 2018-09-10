#pragma once

#include <OSE/Graphics/Resource.h>
#include <OSE/TypeDefs.h>

#include <memory>
#include <string>
#include <vector>

namespace OSE {
    struct GLShaderDescriptor
    {
        enum class Type
        {
            Vertex,
            Fragment
        };

        Type type;
        std::string src;
    };

    class GLProgram : public Resource<GLProgram>
    {
        uint m_Handle{ 0 };

    public:
        static std::unique_ptr<GLProgram> Create(const std::vector<GLShaderDescriptor>& descs);
        static std::unique_ptr<GLProgram> Create(const std::string& vertSrc, const std::string& fragSrc);
        static std::unique_ptr<GLProgram> Create(const std::string& singleSrc);

        ~GLProgram();

        GLProgram(const GLProgram& other) = delete;
        GLProgram(GLProgram&& other) = delete;

        GLProgram& operator=(const GLProgram& other) = delete;
        GLProgram& operator=(GLProgram&& other) = delete;

        uint GetAttributeLocation(const std::string& name) const;
        inline uint GetHandle() const { return m_Handle; }

        //TODO add uniform handling
        uint GetUniformLocation(const std::string& name) const;

        //template<typename T>
        //void SetUniform(const std::string& name, T value);

        void Dispose() override;

    private:
        GLProgram();
    };
}