#include "OSE/Graphics/GLRenderer.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Log.h>

namespace OSE {
    static uint GetGLPrimitive(RenderPrimitive primitive)
    {
        switch (primitive)
        {
        case RenderPrimitive::Triangles:
            return GL_TRIANGLES;
        case RenderPrimitive::TriangleStrip:
            return GL_TRIANGLE_STRIP;
        case RenderPrimitive::Lines:
            return GL_LINES;
        case RenderPrimitive::LineStrip:
            return GL_LINE_STRIP;
        case RenderPrimitive::Points:
            return GL_POINTS;
        case RenderPrimitive::TriangleFan:
            return GL_TRIANGLE_FAN;
        }

        return GL_TRIANGLES;
    }

    GLRenderer::GLRenderer(GLContext* context) : m_Context{ context }
    {

    }

    void GLRenderer::BindProgram(ProgramHandle handle)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        OSE_ASSERT(handle, "Program handle is invalid");
        m_Context->m_ProgramResources.At(handle.GetID())->Bind();
        m_Context->m_CurrentProgram = handle;
    }

    void GLRenderer::BindTexture(TextureHandle handle, uint slot)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        OSE_ASSERT(handle, "Texture handle is invalid");
        m_Context->m_TextureResources.At(handle.GetID())->Bind(slot);
    }


    void GLRenderer::Draw(VertexLayoutHandle layout, RenderPrimitive primitive,
                        BufferHandle vertexBuffer,
                        size_t vertexCount, size_t startVertex)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        OSE_ASSERT(layout, "VertexLayout handle is invalid");
        OSE_ASSERT(vertexBuffer, "VertexBuffer handle is invalid");

        uint glPrimitive = GetGLPrimitive(primitive);

        GLVertexArray* array = m_Context->m_VertexArrayResources.At(layout.GetID());
        GLBuffer* vbo = m_Context->m_BufferResources.At(vertexBuffer.GetID());

        size_t count = array->Bind(*vbo);
        size_t start = 0;
        if (vertexCount > 0)
        {
            count = vertexCount;
            start = startVertex;
        }

        GLCall(glDrawArrays(glPrimitive, start, count))
    }

    void GLRenderer::DrawIndexed(VertexLayoutHandle layout, RenderPrimitive primitive,
                        BufferHandle vertexBuffer, BufferHandle indexBuffer,
                        size_t indexCount, size_t startIndex)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        OSE_ASSERT(layout, "VertexLayout handle is invalid");
        OSE_ASSERT(vertexBuffer, "VertexBuffer handle is invalid");
        OSE_ASSERT(indexBuffer, "IndexBuffer handle is invalid");

        uint glPrimitive = GetGLPrimitive(primitive);

        GLVertexArray* array = m_Context->m_VertexArrayResources.At(layout.GetID());
        GLBuffer* vbo = m_Context->m_BufferResources.At(vertexBuffer.GetID());
        GLBuffer* ibo = m_Context->m_BufferResources.At(indexBuffer.GetID());

        size_t count = array->BindIndexed(*vbo, *ibo);
        size_t start = 0;
        if (indexCount > 0)
        {
            count = indexCount;
            start = startIndex;
        }

        GLCall(glDrawElements(glPrimitive, count, GL_UNSIGNED_SHORT, nullptr))
    }

    void GLRenderer::UpdateBuffer(BufferHandle handle, BufferDescriptor::Type type, const BufferDataDescriptor& data)
    {

    }
}