#include "OSE/Graphics/GLCommon.h"

template<>
bool oseCheckGLExtension<oseGLExtension::VertexArrayObject>()
{
    return true;
}