#include "OSE/Graphics/GLProgramUniform.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Log.h>

namespace OSE {

    template<>
    void GLProgramUniform<float>::Bind(const float& value) const
    {
        glUniform1f(location, value);
    }

    template<>
    void GLProgramUniformV<float>::Bind(const float* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        glUniform1fv(location, count, values);
    }

    template<>
    void GLProgramUniform<int>::Bind(const int& value) const
    {
        glUniform1i(location, value);
    }

    template<>
    void GLProgramUniformV<int>::Bind(const int* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        glUniform1iv(location, count, values);
    }

}