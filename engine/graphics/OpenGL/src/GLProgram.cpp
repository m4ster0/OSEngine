#include "OSE/Graphics/GLProgram.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Log.h>

namespace OSE {

    static uint GetShaderGLType(ShaderType type)
    {
        switch (type)
        {
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;
        case ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
        }

        return 0;
    }

    struct GLShader
    {
        static std::unique_ptr<GLShader> Create(const ShaderDescriptor& desc)
        {
            uint glType{ GetShaderGLType(desc.type) };
            const char* cStr{ desc.src.c_str() };
            std::unique_ptr<GLShader> shader{ new GLShader{ glType } };

            GLCall(glShaderSource(shader->handle, 1, &cStr, NULL));
            GLCall(glCompileShader(shader->handle));

            int success;
            GLCall(glGetShaderiv(shader->handle, GL_COMPILE_STATUS, &success));
            if (success == GL_FALSE)
            {
                int length;
                GLCall(glGetShaderiv(shader->handle, GL_INFO_LOG_LENGTH, &length));
                std::unique_ptr<char[]> message{ new char[length] };
                GLCall(glGetShaderInfoLog(shader->handle, length, &length, message.get()));
                OSE_ERROR("Shader compilation failure: ", message.get());
                return nullptr;
            }

            return shader;
        }

        uint handle{ 0 };

        GLShader(const GLShader& other) = delete;
        GLShader(GLShader&& other) = delete;

        GLShader& operator=(const GLShader& other) = delete;
        GLShader& operator=(GLShader&& other) = delete;

        ~GLShader()
        {
            glDeleteShader(handle);
        }

    private:
        GLShader(uint type)
        {
            handle = glCreateShader(type);
        }
    };

    GLProgram* GLProgram::Create(const std::vector<ShaderDescriptor>& shaderDescs)
    {
        GLProgram* program{ new GLProgram };

        std::vector<std::unique_ptr<GLShader>> shaders;
        for (const auto& desc : shaderDescs)
        {
            std::unique_ptr<GLShader> shader = GLShader::Create(desc);
            if (shader)
            {
                GLCall(glAttachShader(program->m_Handle, shader->handle));
                shaders.push_back(std::move(shader));
            }
        }

        const std::unordered_map<VertexAttrType, std::string>& attrTypes = VertexAttributeDescriptor::TypeName;
        for (auto it = attrTypes.begin(); it != attrTypes.end(); ++it)
        {
            uint location{ static_cast<uint>(it->first) }; //VertexAttribute::Type enum value corresponds to location in shader
            const char* name{ it->second.c_str() }; //VertexAttribute::Type has corresponding name which all shaders must adhere to if using it
            GLCall(glBindAttribLocation(program->m_Handle, location, name));
        }

        GLCall(glLinkProgram(program->m_Handle));

        int success;
        GLCall(glGetProgramiv(program->m_Handle, GL_LINK_STATUS, &success));
        if (success == GL_FALSE)
        {
            int length;
            GLCall(glGetProgramiv(program->m_Handle, GL_INFO_LOG_LENGTH, &length));
            std::unique_ptr<char[]> message{ new char[length] };
            GLCall(glGetProgramInfoLog(program->m_Handle, length, &length, message.get()));
            OSE_ERROR("program linking failure: ", message.get());
        }

        GLCall(glValidateProgram(program->m_Handle));

        return program;
    }

    GLProgram::GLProgram()
    {
        m_Handle = glCreateProgram();
    }

    GLProgram::~GLProgram()
    {
        Dispose();
    }

    void GLProgram::Bind() const
    {
        GLCall(glUseProgram(m_Handle));
    }

    uint GLProgram::GetAttributeLocation(const std::string& name) const
    {
        return glGetAttribLocation(m_Handle, name.c_str());
    }

    uint GLProgram::GetUniformLocation(const std::string& name) const
    {
        return glGetUniformLocation(m_Handle, name.c_str());
    }

    void GLProgram::Dispose()
    {
        if (m_Handle)
            GLCall(glDeleteProgram(m_Handle));

        m_Handle = 0;
    }
}