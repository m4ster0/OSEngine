#pragma once

#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"

#include <string>

namespace OSE {

    struct ProgramUniformBase
    {
        ProgramHandle program;
        std::string name;

        virtual ~ProgramUniformBase() = default;
    };

    //think if checking for bound program is necessary
    template<typename T>
    struct ProgramUniform: public ProgramUniformBase
    {
        virtual void Bind(const T& value) const = 0;
        virtual ~ProgramUniform() = default;
    };

    template<typename T>
    struct ProgramUniformV: public ProgramUniformBase
    {
        size_t size;

        virtual void Bind(const T* values, size_t count) const = 0;
        virtual ~ProgramUniformV() = default;
    };

}