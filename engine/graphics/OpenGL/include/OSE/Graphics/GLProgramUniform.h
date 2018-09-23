#pragma once

#include <OSE/Graphics/GraphicsProgramUniform.h>

#include <memory>

namespace OSE {

    template<typename T>
    struct GLProgramUniform : public ProgramUniform<T>
    {
        uint location;

        void Bind(const T& value) const override;
    };

    template<typename T>
    struct GLProgramUniformV : public ProgramUniformV<T>
    {
        uint location;

        void Bind(const T* values, size_t count) const override;
    };

    template<typename T>
    std::unique_ptr<ProgramUniformBase> createGLProgramUniform(int32 programID, int location, int size)
    {
        if (size > 1)
        {
            GLProgramUniformV<T>* arrayUniform = new GLProgramUniformV<T>;
            arrayUniform->location = location;
            arrayUniform->size = size;
            return std::unique_ptr<ProgramUniformBase>(arrayUniform);
        }

        GLProgramUniform<T>* uniform = new GLProgramUniform<T>;
        uniform->location = location;
        return std::unique_ptr<ProgramUniformBase>(uniform);
    }
}