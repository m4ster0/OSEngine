#include "OSE/Graphics/GLCommon.h"

template<>
bool oseCheckGLExtension<oseGLExtension::VertexArrayObject>()
{
    return GLAD_GL_OES_vertex_array_object > 0;
}