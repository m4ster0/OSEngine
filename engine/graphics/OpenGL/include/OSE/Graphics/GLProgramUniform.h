#pragma once

#include <OSE/Graphics/GraphicsResourceDescriptor.h>

#include <memory>

namespace OSE {

    template<typename T>
    struct GLProgramUniform : public ProgramUniform
    {
        int32 programRID;
        uint location;

        void Bind(const T& value) const;
    };

    template<typename T>
    struct GLProgramUniformV : public ProgramUniform
    {
        int32 programRID;
        uint location;
        size_t size;

        void Bind(const T* values, size_t count) const;
    };

    template<typename T>
    static std::unique_ptr<ProgramUniform> CreateGLProgramUniform(int32 programID, int location, int size)
    {
        if (size > 1)
        {
            GLProgramUniformV<T>* arrayUniform = new GLProgramUniformV<T>;
            arrayUniform->programRID = programID;
            arrayUniform->location = location;
            arrayUniform->size = size;
            return std::unique_ptr<ProgramUniform>(arrayUniform);
        }

        GLProgramUniform<T>* uniform = new GLProgramUniform<T>;
        uniform->programRID = programID;
        uniform->location = location;
        return std::unique_ptr<ProgramUniform>(uniform);
    }
}