#include "OSE/Graphics/GLShader.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Log.h>

#include <memory>

namespace OSE {

    GLShader::GLShader(Type type, const std::string& src):
        m_Type{ type }
    {
        uint glType = GetGLType(type);
        m_Handle = glCreateShader(glType);
        const char* cSrc = src.c_str();
        GLCall(glShaderSource(m_Handle, 1, &cSrc, NULL));
    }

    GLShader::~GLShader()
    {
        Dispose();
    }

    bool GLShader::Compile()
    {
        if (!m_Handle)
            return false;

        GLCall(glCompileShader(m_Handle));

        int success;
        GLCall(glGetShaderiv(m_Handle, GL_COMPILE_STATUS, &success));
        if (success == GL_FALSE)
        {
            int length;
            GLCall(glGetShaderiv(m_Handle, GL_INFO_LOG_LENGTH, &length));
            std::unique_ptr<char[]> message{ new char[length] };
            GLCall(glGetShaderInfoLog(m_Handle, length, &length, message.get()));
            OSE_ERROR("Shader compilation failure: ", message.get());
            Dispose();
            return false;
        }

        return true;
    }

    void GLShader::Dispose()
    {
        if (m_Handle)
        {
            glDeleteShader(m_Handle);
            m_Handle = 0;
        }
    }

    uint GetGLType(GLShader::Type type)
    {
        using ShaderType = GLShader::Type;
        switch (type)
        {
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;
        case ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
        }

        return 0;
    }
}