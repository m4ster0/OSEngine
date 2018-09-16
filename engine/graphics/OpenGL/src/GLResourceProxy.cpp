#include "OSE/Graphics/GLResourceProxy.h"

#include <OSE/Log.h>

namespace OSE {

    GLResourceProxy::GLResourceProxy(GLContext* context):
        m_Context{ context }
    {

    }

    ProgramHandle GLResourceProxy::CreateProgram(const std::vector<ShaderDescriptor>& shaderDescriptors)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. ResourceProxy must be recreated onLoad");

        ProgramHandle handle = ProgramHandle::Invalid;
        if (m_Context->m_ProgramResources.HasNext())
        {
            GLProgram* program = GLProgram::Create(shaderDescriptors);

            int32 index = m_Context->m_ProgramResources.PutNext(program);
            handle = ProgramHandle{ index };
        }

        return handle;
    }

    void GLResourceProxy::DisposeProgram(ProgramHandle handle)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. ResourceProxy must be recreated onLoad");
        OSE_ASSERT(handle, "Program handle is invalid");

        m_Context->m_ProgramResources.Remove(handle.GetID());
    }


    BufferHandle GLResourceProxy::CreateBuffer(BufferDescriptor::Type type, const BufferDescriptor& desc, const BufferDataDescriptor* dataDesc)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. ResourceProxy must be recreated onLoad");

        BufferHandle handle = BufferHandle::Invalid;
        if (m_Context->m_BufferResources.HasNext())
        {
            GLBuffer* buffer{ new GLBuffer(type, desc.size, desc.byteSize, desc.isStatic) };

            if (dataDesc)
            {
                buffer->Bind();
                buffer->Write(dataDesc->data, dataDesc->length, dataDesc->offset, dataDesc->discardAll);
            }

            int32 index = m_Context->m_BufferResources.PutNext(buffer);
            handle = BufferHandle{ index };
        }

        return handle;
    }

    void GLResourceProxy::DisposeBuffer(BufferHandle handle)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. ResourceProxy must be recreated onLoad");
        OSE_ASSERT(handle, "BufferHandle handle is invalid");

        m_Context->m_BufferResources.Remove(handle.GetID());
    }


    VertexLayoutHandle GLResourceProxy::CreateVertexLayout(const std::vector<VertexAttributeDescriptor>& attributeDescriptors)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. ResourceProxy must be recreated onLoad");

        VertexLayoutHandle handle = VertexLayoutHandle::Invalid;
        if (m_Context->m_VertexArrayResources.HasNext())
        {
            GLVertexLayout layout{ attributeDescriptors };
            GLVertexArray* vertArray{ new GLVertexArray(layout) };

            int32 index = m_Context->m_VertexArrayResources.PutNext(vertArray);
            handle = VertexLayoutHandle{ index };
        }

        return handle;
    }

    void GLResourceProxy::DisposeVertexLayout(VertexLayoutHandle handle)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. ResourceProxy must be recreated onLoad");
        OSE_ASSERT(handle, "VertexLayout handle is invalid");

        m_Context->m_VertexArrayResources.Remove(handle.GetID());
    }


    void GLResourceProxy::GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        OSE_ASSERT(layout, "VertexLayout handle is invalid");
        OSE_ASSERT(vertexBuffer, "VertexBuffer handle is invalid");

        GLVertexArray* array = m_Context->m_VertexArrayResources.At(layout.GetID());
        GLBuffer* vbo = m_Context->m_BufferResources.At(vertexBuffer.GetID());

        array->MakeVAO(*vbo);
    }

    void GLResourceProxy::GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer, BufferHandle indexBuffer)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        OSE_ASSERT(layout, "VertexLayout handle is invalid");
        OSE_ASSERT(vertexBuffer, "VertexBuffer handle is invalid");
        OSE_ASSERT(indexBuffer, "IndexBuffer handle is invalid");

        GLVertexArray* array = m_Context->m_VertexArrayResources.At(layout.GetID());
        GLBuffer* vbo = m_Context->m_BufferResources.At(vertexBuffer.GetID());
        GLBuffer* ibo = m_Context->m_BufferResources.At(indexBuffer.GetID());

        array->MakeVAO(*vbo, *ibo);
    }

    TextureHandle GLResourceProxy::CreateTexture(const TextureDescriptor& desc, const Image* image)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. ResourceProxy must be recreated onLoad");

        TextureHandle handle = TextureHandle::Invalid;
        if (m_Context->m_TextureResources.HasNext())
        {
            GLTexture* texture{ new GLTexture() };
            texture->Bind();
            texture->SetParameters(desc);

            if (image)
                texture->UploadData(*image);

            int32 index = m_Context->m_TextureResources.PutNext(texture);
            handle = TextureHandle{ index };
        }

        return handle;
    }

    void GLResourceProxy::DisposeTexture(TextureHandle handle)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. ResourceProxy must be recreated onLoad");
        OSE_ASSERT(handle, "Texture handle is invalid");

        m_Context->m_TextureResources.Remove(handle.GetID());
    }
}