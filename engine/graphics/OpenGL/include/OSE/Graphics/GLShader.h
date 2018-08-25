#pragma once

#include <OSE/TypeDefs.h>

#include <string>

namespace OSE {

    class GLShader
    {
    public:
        enum class Type
        {
            Vertex,
            Fragment
        };

    private:
        friend class GLProgram;

        uint m_Handle{ 0 };
        Type m_Type;

    public:
        GLShader(Type type, const std::string& src);
        ~GLShader();

        //GLShader(const GLShader& other) = delete;
        //GLShader(GLShader&& other) = delete;

        //GLShader& operator=(const GLShader& other) = delete;
        //GLShader& operator=(GLShader&& other) = delete;

        inline Type GetType() const { return m_Type; }

        bool Compile();
        void Dispose();
    };

    uint GetGLType(GLShader::Type type);

}