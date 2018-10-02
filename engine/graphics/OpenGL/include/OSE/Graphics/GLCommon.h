#pragma once

#include <OSE/Log.h>

#include <glad/glad.h>

enum class oseGLExtension
{
    VertexArrayObject
};

template<oseGLExtension extension>
bool oseCheckGLExtension() = delete;

template<>
bool oseCheckGLExtension<oseGLExtension::VertexArrayObject>();

#ifdef ANDROID
#define glBindVertexArray glBindVertexArrayOES
#define glDeleteVertexArrays glDeleteVertexArraysOES
#define glGenVertexArrays glGenVertexArraysOES
#define glIsVertexArray glIsVertexArrayOES
#endif

inline void oseClearGLError()
{
    while (glGetError() != GL_NO_ERROR);
}

inline void oseCheckGLError(const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        OSE_DEBUG("OpenGL Error(", file, ":", line, ") - ", error);
    }
}

#ifdef DEBUG_OSE
    #define GLCall(x)   { \
                        oseClearGLError(); \
                        x; \
                        oseCheckGLError(__FILE__, __LINE__); \
                        }
#else
    #define GLCall(x) x;
#endif // DEBUG
