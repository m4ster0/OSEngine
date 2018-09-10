#pragma once

#include "OSE/Graphics/GLProgram.h"
#include "OSE/Graphics/GLVertexDescriptor.h"
#include "OSE/Graphics/GLVertexBuffer.h"
#include "OSE/Graphics/GLIndexBuffer.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/TypeDefs.h>

namespace OSE {
    enum class RenderPrimitive : uint
    {
        Points = GL_POINTS,
        Lines = GL_LINES,
        LineStrip = GL_LINE_STRIP,
        Triangles = GL_TRIANGLES,
        TriangleStrip = GL_TRIANGLE_STRIP,
        TriangleFan = GL_TRIANGLE_FAN
    };

    class GLRenderer
    {
        //properties state cache

    public:
        //draw calls
        void render(const GLProgram& program,
            RenderPrimitive primitive,
            const GLVertexDescriptor& vertexDescriptor,
            const GLVertexBuffer& vertBuffer);

        void render(const GLProgram& program,
            RenderPrimitive primitive,
            const GLVertexDescriptor& vertexDescriptor,
            const GLVertexBuffer& vertBuffer,
            const GLIndexBuffer& indexBuffer);
    };
}