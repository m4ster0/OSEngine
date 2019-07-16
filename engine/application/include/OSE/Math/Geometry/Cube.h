#pragma once

#include "OSE/Math/Geometry/Geometry.h"
#include "OSE/Math/Vector.h"

namespace OSE {

    class CubeBuilder: public GeometryBuilder
    {
    public:
        CubeBuilder() = default;

        Geometry build() override;
    };

}
