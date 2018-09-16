#include "OSE/Graphics/GLTexture.h"
#include "OSE/Graphics/GLCommon.h"

namespace OSE {

    static uint formatToGL(Image::Format format)
    {
        switch (format)
        {
        case Image::Format::RGB:
            return GL_RGB;
        case Image::Format::RGBA:
            return GL_RGBA;
        }
    }

    static uint formatToChannelSize(Image::Format format)
    {
        switch (format)
        {
        case Image::Format::RGB:
        case Image::Format::RGBA:
            return GL_UNSIGNED_BYTE;
        }
    }

    static uint wrapToGL(TexWrapType type)
    {
        switch (type)
        {
        case TexWrapType::Repeat:
            return GL_REPEAT;
        case TexWrapType::MirrorRepeat:
            return GL_MIRRORED_REPEAT;
        case TexWrapType::EdgeClamp:
            return GL_CLAMP_TO_EDGE;
        case TexWrapType::BorderClamp:
            return GL_CLAMP_TO_BORDER;
        }
    }

    static uint filterToGL(TexFilterType type)
    {
        switch (type)
        {
        case TexFilterType::Nearest:
            return GL_NEAREST;
        case TexFilterType::Linear:
            return GL_LINEAR;
        }
    }

    GLTexture::GLTexture()
    {
        GLCall(glGenTextures(1, &m_Handle));
        OSE_ASSERT(m_Handle, "Could not create texture");
    }

    GLTexture::~GLTexture()
    {
        Dispose();
    }

    void GLTexture::Bind(uint slot)
    {
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_Handle));
    }

    void GLTexture::UploadData(const Image& image)
    {
        m_Format = image.GetFormat();
        uint glFormat = formatToGL(m_Format);
        uint channelByteSize = formatToChannelSize(m_Format);

        m_Width = image.GetWidth();
        m_Height = image.GetHeight();

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, glFormat, m_Width, m_Height, 0, glFormat, channelByteSize, image.GetData()));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }

    void GLTexture::SetParameters(const TextureDescriptor& desc)
    {
        SetWrap(desc.wrap);

        SetMinifyFilter(desc.minifyFilter);
        SetMagnifyFilter(desc.magnifyFilter);
    }

    void GLTexture::SetWrap(TexWrapType wrapMode)
    {
        uint glWrap = wrapToGL(wrapMode);
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap));
    }

    void GLTexture::SetMinifyFilter(TexFilterType filterMode)
    {
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterToGL(filterMode)));
    }

    void GLTexture::SetMagnifyFilter(TexFilterType filterMode)
    {
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterToGL(filterMode)));
    }

    void GLTexture::Dispose()
    {
        if (m_Handle)
        {
            glDeleteTextures(1, &m_Handle);
            m_Handle = 0;
        }
    }
}