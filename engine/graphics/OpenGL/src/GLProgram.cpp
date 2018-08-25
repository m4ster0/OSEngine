#include "OSE/Graphics/GLProgram.h"
#include "OSE/Graphics/GLShader.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Log.h>

namespace OSE {

    GLProgram::GLProgram():
        m_Handle{ glCreateProgram() }
    {

    }

    GLProgram::~GLProgram()
    {
        Dispose();
    }

    void GLProgram::Begin()
    {
        glUseProgram(m_Handle);
    }

    void GLProgram::End()
    {
        glUseProgram(0);
    }

    uint GLProgram::GetAttributeLocation(const std::string& name)
    {
        return glGetAttribLocation(m_Handle, name.c_str());
    }

    void GLProgram::Dispose()
    {
        if (m_Handle)
        {
            GLCall(glDeleteProgram(m_Handle));
            m_Handle = 0;
        }
    }

    void GLProgram::AttachShader(const GLShader& shader)
    {
        GLCall(glAttachShader(m_Handle, shader.m_Handle));
    }

    void GLProgram::BindAttribute(uint location, const std::string& name)
    {
        GLCall(glBindAttribLocation(m_Handle, location, name.c_str()));
    }

    bool GLProgram::Link()
    {
        GLCall(glLinkProgram(m_Handle));

        int success;
        GLCall(glGetProgramiv(m_Handle, GL_LINK_STATUS, &success));
        if ( success == GL_FALSE )
        {
            int length;
            GLCall(glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &length));
            std::unique_ptr<char[]> message{ new char[length] };
            GLCall(glGetProgramInfoLog(m_Handle, length, &length, message.get()));
            OSE_ERROR("program linking failure: ", message.get());
            return false;
        }

        GLCall(glValidateProgram(m_Handle));

        return true;
    }

    /* ************************ */
    /* ******* Builder ******** */
    /* ************************ */
    GLProgram::Builder::Builder()
    {

    }

    bool GLProgram::Builder::HasShader(GLShader::Type type)
    {
        for (auto& shader : m_Shaders)
        {
            if (shader->GetType() == type)
                return true;
        }

        return false;
    }

    GLProgram::Builder& GLProgram::Builder::AddShader(GLShader::Type type, const std::string& source)
    {
        std::unique_ptr<GLShader> shader{ new GLShader{ type, source } };
        if (!HasShader(type) && shader->Compile())
            m_Shaders.push_back(shader);

        return *this;
    }

    GLProgram::Builder& GLProgram::Builder::BindAttribute(uint location, const std::string& name)
    {
        m_AttribBinds[name] = location;
        return *this;
    }

    std::unique_ptr<GLProgram> GLProgram::Builder::Create()
    {
        std::unique_ptr<GLProgram> result{ new GLProgram };

        for (auto& shader : m_Shaders)
            result->AttachShader(*shader);

        for (auto it = m_AttribBinds.begin(); it != m_AttribBinds.end(); ++it)
            result->BindAttribute(it->second, it->first);

        if (result->Link())
            return result;

        return nullptr;
    }

    GLProgram::SingleSrcBuilder::SingleSrcBuilder(const std::string& source):
        m_Source{ source }
    {

    }

    GLProgram::SingleSrcBuilder::SingleSrcBuilder(const FileSystem& fileSystem, 
                                                  const std::string& devicePath)
    {
        //TODO
    }

    GLProgram::SingleSrcBuilder::SingleSrcBuilder(const FileSystem& fileSystem, 
                                                  const std::string& device, 
                                                  const std::string& path)
    {
        std::unique_ptr<File> file = fileSystem.OpenFileSync(device, path, FileMode::Read);
        if (file)
            file->Read(m_Source);
    }


    GLProgram::Builder& GLProgram::SingleSrcBuilder::AddShader(GLShader::Type type, const std::string& typeTag)
    {
        static const std::string tag{ "#shader" };

        std::string startTag = tag + " " + typeTag;
        std::string::size_type start{ m_Source.find(startTag) };
        std::size_t startPos = start + startTag.length();

        std::string::size_type end{ 0 };
        if (start != std::string::npos && (end = m_Source.find(tag, startPos)))
            return Builder::AddShader( type, m_Source.substr(startPos, end - startPos) );

        return *this;
    }


}