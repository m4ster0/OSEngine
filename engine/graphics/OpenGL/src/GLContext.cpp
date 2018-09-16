#include "OSE/Graphics/GLContext.h"

namespace OSE {

    GLContext::GLContext():
        m_ProgramResources{ 50 }, m_BufferResources{ 500 }, m_VertexArrayResources{ 50 }, m_TextureResources{ 50 }
    {

    }

    void GLContext::Dispose()
    {
        m_ProgramResources.Clear();
        m_BufferResources.Clear();
        m_VertexArrayResources.Clear();
        m_TextureResources.Clear();
    }
}