#include "OSE/Graphics/GLRenderer.h"
#include "OSE/Graphics/GLProgramUniform.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Log.h>

#define OSE_ASSERT_UNIFORM(uniform, programHandle) \
    OSE_ASSERT(uniform, "value type error for given uniform"); \
    OSE_ASSERT(uniform->programRID == programHandle.GetID(), "uniform's program must be active");

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

    void GLRenderer::SetProgramUniform(const ProgramUniform& uniform, int value)
    {
        OSE_ASSERT(m_Context->m_CurrentProgram, "there must be active program");

        const GLProgramUniform<int>* glUniform = dynamic_cast<const GLProgramUniform<int>*>(&uniform);
        OSE_ASSERT_UNIFORM(glUniform, m_Context->m_CurrentProgram);
        glUniform->Bind(value);
    }

    void GLRenderer::SetProgramUniform(const ProgramUniform& uniform, const int* values, size_t count)
    {
        OSE_ASSERT(m_Context->m_CurrentProgram, "there must be active program");

        const GLProgramUniformV<int>* glUniform = dynamic_cast<const GLProgramUniformV<int>*>(&uniform);
        OSE_ASSERT_UNIFORM(glUniform, m_Context->m_CurrentProgram);
        glUniform->Bind(values, count);
    }

    void GLRenderer::SetProgramUniform(const ProgramUniform& uniform, float value)
    {
        OSE_ASSERT(m_Context->m_CurrentProgram, "there must be active program");

        const GLProgramUniform<float>* glUniform = dynamic_cast<const GLProgramUniform<float>*>(&uniform);
        OSE_ASSERT_UNIFORM(glUniform, m_Context->m_CurrentProgram);
        glUniform->Bind(value);
    }

    void GLRenderer::SetProgramUniform(const ProgramUniform& uniform, const float* values, size_t count)
    {
        OSE_ASSERT(m_Context->m_CurrentProgram, "there must be active program");

        const GLProgramUniformV<float>* glUniform = dynamic_cast<const GLProgramUniformV<float>*>(&uniform);
        OSE_ASSERT_UNIFORM(glUniform, m_Context->m_CurrentProgram);
        glUniform->Bind(values, count);
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