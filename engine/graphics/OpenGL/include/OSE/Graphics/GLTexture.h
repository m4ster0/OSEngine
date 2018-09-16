
#include "OSE/Graphics/GLResource.h"

#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/Resources/Image.h>

#include <OSE/TypeDefs.h>

namespace OSE {

    class GLTexture : public GLResource
    {
        uint m_Handle{ 0 };

        size_t m_Width{ 0 };
        size_t m_Height{ 0 };
        Image::Format m_Format;
    public:
        GLTexture();
        ~GLTexture();

        GLTexture(GLTexture&&) = delete;
        GLTexture& operator=(GLTexture&&) = delete;

        void Bind(uint slot = 0);
        void UploadData(const Image& image);

        void SetParameters(const TextureDescriptor& desc);
        void SetWrap(TexWrapType wrapMode);
        void SetMinifyFilter(TexFilterType filterMode);
        void SetMagnifyFilter(TexFilterType filterMode);

        void Dispose() override;
    };

}