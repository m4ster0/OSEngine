#include "OSE/Graphics/GLRenderer.h"
#include "OSE/Graphics/GLCommon.h"

namespace OSE {
    void BindVertexDescriptor(const GLVertexDescriptor& desc)
    {
        size_t offset{ 0 };
        for (const GLVertexAttribute& attr : desc.GetAttributes())
        {
            uint pos = static_cast<uint>(attr.type);
            GLCall(glEnableVertexAttribArray(pos));
            GLCall(glVertexAttribPointer(pos, attr.size, GL_FLOAT, attr.normalized, desc.GetByteSize(), (const void*)offset));
            offset += (attr.size * sizeof(float));
        }
    }

    void GLRenderer::render(const GLProgram& program, RenderPrimitive primitive,
        const GLVertexDescriptor& vertexDescriptor, const GLVertexBuffer& vertBuffer)
    {
        GLCall(glUseProgram(program.GetHandle()));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertBuffer.GetHandle()));

        BindVertexDescriptor(vertexDescriptor);

        GLCall(glDrawArrays(static_cast<uint>(primitive), 0, vertBuffer.GetSize()))
    }

    void GLRenderer::render(const GLProgram& program, RenderPrimitive primitive,
        const GLVertexDescriptor& vertexDescriptor, const GLVertexBuffer& vertBuffer, const GLIndexBuffer& indexBuffer)
    {
        GLCall(glUseProgram(program.GetHandle()));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertBuffer.GetHandle()));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.GetHandle()));

        BindVertexDescriptor(vertexDescriptor);

        size_t elementCount{ indexBuffer.GetSize() };
        GLCall(glDrawElements(static_cast<uint>(primitive), elementCount, GL_UNSIGNED_SHORT, NULL));
    }
}