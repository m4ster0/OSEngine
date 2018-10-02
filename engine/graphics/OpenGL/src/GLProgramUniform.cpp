#include "OSE/Graphics/GLProgramUniform.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Math/Math.h>
#include <OSE/Log.h>

namespace OSE {

    //float
    template<>
    void GLProgramUniform<float>::Bind(const float& value) const
    {
        GLCall(glUniform1f(location, value));
    }

    template<>
    void GLProgramUniformV<float>::Bind(const float* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniform1fv(location, count, values));
    }

    //int
    template<>
    void GLProgramUniform<int>::Bind(const int& value) const
    {
        GLCall(GLCall(glUniform1i(location, value)));
    }

    template<>
    void GLProgramUniformV<int>::Bind(const int* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(GLCall(glUniform1iv(location, count, values)));
    }

    //vec2
    template<>
    void GLProgramUniform<Vec2>::Bind(const Vec2& value) const
    {
        GLCall(glUniform2f(location, value.x, value.y));
    }

    template<>
    void GLProgramUniformV<Vec2>::Bind(const Vec2* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniform2fv(location, count, reinterpret_cast<const float*>(values)));
    }

    //vec3
    template<>
    void GLProgramUniform<Vec3>::Bind(const Vec3& value) const
    {
        GLCall(glUniform3f(location, value.x, value.y, value.z));
    }

    template<>
    void GLProgramUniformV<Vec3>::Bind(const Vec3* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniform3fv(location, count, reinterpret_cast<const float*>(values)));
    }

    //vec4
    template<>
    void GLProgramUniform<Vec4>::Bind(const Vec4& value) const
    {
        GLCall(glUniform4f(location, value.x, value.y, value.z, value.w));
    }

    template<>
    void GLProgramUniformV<Vec4>::Bind(const Vec4* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniform4fv(location, count, reinterpret_cast<const float*>(values)));
    }

    //ivec2
    template<>
    void GLProgramUniform<IVec2>::Bind(const IVec2& value) const
    {
        GLCall(glUniform2i(location, value.x, value.y));
    }

    template<>
    void GLProgramUniformV<IVec2>::Bind(const IVec2* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniform2iv(location, count, reinterpret_cast<const int*>(values)));
    }

    //ivec3
    template<>
    void GLProgramUniform<IVec3>::Bind(const IVec3& value) const
    {
        GLCall(glUniform3i(location, value.x, value.y, value.z));
    }

    template<>
    void GLProgramUniformV<IVec3>::Bind(const IVec3* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniform3iv(location, count, reinterpret_cast<const int*>(values)));
    }

    //ivec4
    template<>
    void GLProgramUniform<IVec4>::Bind(const IVec4& value) const
    {
        GLCall(glUniform4i(location, value.x, value.y, value.z, value.w));
    }

    template<>
    void GLProgramUniformV<IVec4>::Bind(const IVec4* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniform4iv(location, count, reinterpret_cast<const int*>(values)));
    }

    //mat2
    template<>
    void GLProgramUniform<Mat2>::Bind(const Mat2& value) const
    {
        GLCall(glUniformMatrix2fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(&value)));
    }

    template<>
    void GLProgramUniformV<Mat2>::Bind(const Mat2* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniformMatrix2fv(location, count, GL_FALSE, reinterpret_cast<const float*>(&values)));
    }

    //mat3
    template<>
    void GLProgramUniform<Mat3>::Bind(const Mat3& value) const
    {
        GLCall(glUniformMatrix3fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(&value)));
    }

    template<>
    void GLProgramUniformV<Mat3>::Bind(const Mat3* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniformMatrix3fv(location, count, GL_FALSE, reinterpret_cast<const float*>(&values)));
    }

    //mat4
    template<>
    void GLProgramUniform<Mat4>::Bind(const Mat4& value) const
    {
//        Mat4 transposedValue = Math::transpose(value);
        GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(&value)));
    }

    template<>
    void GLProgramUniformV<Mat4>::Bind(const Mat4* values, size_t count) const
    {
        OSE_ASSERT(count <= size, "Wrong size of array uniform");
        GLCall(glUniformMatrix4fv(location, count, GL_FALSE, reinterpret_cast<const float*>(&values)));
    }

}