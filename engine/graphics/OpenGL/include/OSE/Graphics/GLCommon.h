#pragma once

#include <OSE/Log.h>

#if defined(WIN32)
    #include <GL/glew.h>
#elif defined(ANDROID)
    #include <GLES2/gl2.h>
#endif

static void ClearGLError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void CheckGLError(const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        OSE_DEBUG("OpenGL Error(", file, ":", line, ") - ", error);
    }
}

#ifdef DEBUG_OSE
    #define GLCall(x)   ClearGLError(); \
                        x; \
                        CheckGLError(__FILE__, __LINE__);
#else
    #define GLCall(x) x;
#endif // DEBUG
