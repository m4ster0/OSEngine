#include "OSE/Graphics/GLRenderer.h"
#include "OSE/Graphics/GLCommon.h"

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

    GLRenderer::GLRenderer(const GLContext* context) : m_Context{ context }
    {

    }

    GLRenderer::~GLRenderer()
    {

    }

    void GLRenderer::BindProgram(ProgramHandle handle)
    {
        m_Context->GetProgram(handle)->Bind();
    }

    void GLRenderer::GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer)
    {
        GLVertexArray* array = m_Context->GetVertexArray(layout);
        GLBuffer* vbo = m_Context->GetBuffer(vertexBuffer);

        array->MakeVAO(*vbo);
    }

    void GLRenderer::GroupVertices(VertexLayoutHandle layout, BufferHandle vertexBuffer, BufferHandle indexBuffer)
    {
        GLVertexArray* array = m_Context->GetVertexArray(layout);
        GLBuffer* vbo = m_Context->GetBuffer(vertexBuffer);
        GLBuffer* ibo = m_Context->GetBuffer(indexBuffer);

        array->MakeVAO(*vbo, *ibo);
    }

    void GLRenderer::Draw(VertexLayoutHandle layout, RenderPrimitive primitive,
                        BufferHandle vertexBuffer, BufferHandle indexBuffer,
                        size_t vertexCount, size_t startVertex)
    {
        uint glPrimitive = GetGLPrimitive(primitive);

        GLVertexArray* array = m_Context->GetVertexArray(layout);
        GLBuffer* vbo = m_Context->GetBuffer(vertexBuffer);

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
        uint glPrimitive = GetGLPrimitive(primitive);

        GLVertexArray* array = m_Context->GetVertexArray(layout);
        GLBuffer* vbo = m_Context->GetBuffer(vertexBuffer);
        GLBuffer* ibo = m_Context->GetBuffer(indexBuffer);

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