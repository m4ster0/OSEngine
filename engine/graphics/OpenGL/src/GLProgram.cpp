#include "OSE/Graphics/GLProgram.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Math/Vector.h>
#include <OSE/Math/Matrix.h>
#include <OSE/Log.h>

#include <cstring>

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

        GLShader(GLShader&& other) = delete;
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

    GLProgram::GLProgram(int32 id, const std::vector<ShaderDescriptor>& descs):
        GLResource(id)
    {
        m_Handle = glCreateProgram();
        Preprocess();
        Compile(descs);
        CreateUniformCache();
    }


    GLProgram::~GLProgram()
    {
        Dispose();
    }

    void GLProgram::Preprocess()
    {

    }

    void GLProgram::Compile(const std::vector<ShaderDescriptor>& descs)
    {
        std::vector<std::unique_ptr<GLShader>> shaders;
        for (const auto& desc : descs)
        {
            std::unique_ptr<GLShader> shader = GLShader::Create(desc);
            if (shader)
            {
                GLCall(glAttachShader(m_Handle, shader->handle));
                shaders.push_back(std::move(shader));
            }
        }

        std::unordered_map<VertexAttrType, std::string, EnumTypeHasher>& attrTypes = VertexAttributeDescriptor::TypeName;
        for (auto it = attrTypes.begin(); it != attrTypes.end(); ++it)
        {
            uint location{ static_cast<uint>(it->first) }; //VertexAttribute::Type enum value corresponds to location in shader
            const char* name{ it->second.c_str() }; //VertexAttribute::Type has corresponding name which all shaders must adhere to if using it
            GLCall(glBindAttribLocation(m_Handle, location, name));
        }

        GLCall(glLinkProgram(m_Handle));

        int success;
        GLCall(glGetProgramiv(m_Handle, GL_LINK_STATUS, &success));
        if (success == GL_FALSE)
        {
            int length;
            GLCall(glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &length));
            std::unique_ptr<char[]> message{ new char[length] };
            GLCall(glGetProgramInfoLog(m_Handle, length, &length, message.get()));
            OSE_ERROR("program linking failure: ", message.get());
        }

        GLCall(glValidateProgram(m_Handle));
    }

    void GLProgram::CreateUniformCache()
    {
        //Querying uniforms for caching
        int activeUniforms, nameLength;
        GLCall(glGetProgramiv(m_Handle, GL_ACTIVE_UNIFORMS, &activeUniforms));
        GLCall(glGetProgramiv(m_Handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nameLength));
        if (activeUniforms && nameLength)
        {
            auto formatName = [](const char* name) -> std::string {
                int len = std::strlen(name);
                auto endsWith = [name, len](const char* ending) {
                    int endingStart = len - std::strlen(ending);
                    return endingStart && std::strcmp(name + endingStart, ending) == 0;
                };

                if (endsWith("[0]"))
                    return std::string(name, len - 3);

                return std::string(name);
            };

            std::unique_ptr<char[]> rawUniformName{ new char[nameLength + 1] };
            int uniformSize;
            GLenum uniformType;
            for (int i = 0; i < activeUniforms; ++i)
            {
                GLCall(glGetActiveUniform(m_Handle, i, nameLength, NULL, &uniformSize, &uniformType, rawUniformName.get()));
                std::string uniformName{ formatName(rawUniformName.get()) };

                std::unique_ptr<ProgramUniformBase> uniform = CreateUniform(uniformName, uniformType, uniformSize);
                uniform->program = ProgramHandle(rid);
                uniform->name = uniformName;
                m_Uniforms[uniformName] = std::move(uniform);
            }
        }
    }

    std::unique_ptr<ProgramUniformBase> GLProgram::CreateUniform(const std::string& name, uint type, int size)
    {
        int location = GetUniformLocation(name);
        OSE_ASSERT(location >= 0, name + " uniform does not correspond to an active uniform");
        switch (type)
        {
        case GL_FLOAT:
            return createGLProgramUniform<float>(rid, location, size);
        case GL_INT:
        case GL_SAMPLER_2D:
            return createGLProgramUniform<int>(rid, location, size);
        case GL_FLOAT_VEC2:
            return createGLProgramUniform<Vec2>(rid, location, size);
        case GL_FLOAT_VEC3:
            return createGLProgramUniform<Vec3>(rid, location, size);
        case GL_FLOAT_VEC4:
            return createGLProgramUniform<Vec4>(rid, location, size);
        case GL_INT_VEC2:
            return createGLProgramUniform<IVec2>(rid, location, size);
        case GL_INT_VEC3:
            return createGLProgramUniform<IVec3>(rid, location, size);
        case GL_INT_VEC4:
            return createGLProgramUniform<IVec4>(rid, location, size);
        case GL_FLOAT_MAT2:
            return createGLProgramUniform<Mat2>(rid, location, size);
        case GL_FLOAT_MAT3:
            return createGLProgramUniform<Mat3>(rid, location, size);
        case GL_FLOAT_MAT4:
            return createGLProgramUniform<Mat4>(rid, location, size);
        }

        OSE_ERROR("not supported uniform gl_type: ", type);
        return nullptr;
    }

    int GLProgram::GetAttributeLocation(const std::string& name) const
    {
        return glGetAttribLocation(m_Handle, name.c_str());
    }

    int GLProgram::GetUniformLocation(const std::string& name) const
    {
        return glGetUniformLocation(m_Handle, name.c_str());
    }

    void GLProgram::Bind() const
    {
        GLCall(glUseProgram(m_Handle));
    }

    ProgramUniformBase* GLProgram::GetUniform(const std::string& name) const
    {
        auto it = m_Uniforms.find(name);
        if (it != m_Uniforms.end())
            return it->second.get();

        return nullptr;
    }

    void GLProgram::Dispose()
    {
        if (m_Handle)
            glDeleteProgram(m_Handle);

        m_Handle = 0;
    }
}