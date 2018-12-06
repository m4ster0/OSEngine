#include "OSE/Graphics/GLRenderer.h"
#include "OSE/Graphics/GLContext.h"
#include "OSE/Graphics/GLProgramUniform.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Log.h>

#define OSE_ASSERT_UNIFORM(uniform, programHandle) \
    OSE_ASSERT(uniform, "value type error for given uniform"); \
    OSE_ASSERT(uniform->programRID == programHandle.GetID(), "uniform's program must be active");

namespace OSE {
    namespace
    {
        constexpr uint GetGLPrimitive(RenderPrimitive primitive)
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

        inline void SetGLStateCapability(uint capability, bool enabled)
        {
            if (enabled)
                GLCall(glEnable(capability))
            else
                GLCall(glDisable(capability))
        }

        constexpr uint GetGLBlendFactor(GraphicsBlendFactor factor)
        {
            switch (factor)
            {
            case GraphicsBlendFactor::Zero:
                return GL_ZERO;
            case GraphicsBlendFactor::One:
                return GL_ONE;
            case GraphicsBlendFactor::SrcAlpha:
                return GL_SRC_ALPHA;
            case GraphicsBlendFactor::OneMinusSrcAlpha:
                return GL_ONE_MINUS_SRC_ALPHA;
            case GraphicsBlendFactor::DstAlpha:
                return GL_DST_ALPHA;
            case GraphicsBlendFactor::OneMinusDstAlpha:
                return GL_ONE_MINUS_DST_ALPHA;
            }

            return 0;
        }

        constexpr uint GetGLTestFunction(GraphicsTestFunction func)
        {
            switch (func)
            {
            case GraphicsTestFunction::Never:
                return GL_NEVER;
            case GraphicsTestFunction::Always:
                return GL_ALWAYS;
            case GraphicsTestFunction::Equal:
                return GL_EQUAL;
            case GraphicsTestFunction::NotEqual:
                return GL_NOTEQUAL;
            case GraphicsTestFunction::Greater:
                return GL_GREATER;
            case GraphicsTestFunction::GreaterEqual:
                return GL_GEQUAL;
            case GraphicsTestFunction::Less:
                return GL_LESS;
            case GraphicsTestFunction::LessEqual:
                return GL_LEQUAL;
            }

            return 0;
        }
    }

    GLRenderer::GLRenderer(GLContext* context) : m_Context{ context }
    {

    }

    void GLRenderer::SetViewport(uint x, uint y, uint width, uint height)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        GLCall(glViewport(x, y, width, height));
    }

    void GLRenderer::SetClearColor(const Color& color)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        GLCall(glClearColor(color.r, color.g, color.b, color.a));
    }

    void GLRenderer::SetClearColor(float r, float g, float b, float a)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        GLCall(glClearColor(r, g, b, a));
    }

    void GLRenderer::SetBlend(bool enabled)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        SetGLStateCapability(GL_BLEND, enabled);
    }

    void GLRenderer::SetBlendFunc(GraphicsBlendFactor srcFactor, GraphicsBlendFactor dstFactor)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        GLCall(glBlendFunc(GetGLBlendFactor(srcFactor), GetGLBlendFactor(dstFactor)));
    }

    void GLRenderer::SetDepthTest(bool enabled)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        SetGLStateCapability(GL_DEPTH_TEST, enabled);
    }

    void GLRenderer::SetDepthTestFunc(GraphicsTestFunction func)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        GLCall(glDepthFunc(GetGLTestFunction(func)));
    }

    void GLRenderer::SetStencilTest(bool enabled)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        SetGLStateCapability(GL_STENCIL_TEST, enabled);
    }

    void GLRenderer::SetStencilTestFunc(GraphicsTestFunction func)
    {
        //OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        //GLCall(glStencilFunc(GetGLTestFunction(func)));
    }

    void GLRenderer::SetCullFace(bool enabled)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        SetGLStateCapability(GL_CULL_FACE, enabled);
    }

    void GLRenderer::Clear(GraphicsBufferMode modes)
    {
        OSE_ASSERT(m_Context, "Context has been destroyed. Renderer must be recreated onLoad");
        uint buffers = 0;
        if (static_cast<bool>(modes & GraphicsBufferMode::Color))
            buffers |= GL_COLOR_BUFFER_BIT;
        if (static_cast<bool>(modes & GraphicsBufferMode::Depth))
            buffers |= GL_DEPTH_BUFFER_BIT;
        if (static_cast<bool>(modes & GraphicsBufferMode::Stencil))
            buffers |= GL_STENCIL_BUFFER_BIT;

        GLCall(glClear(buffers));
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