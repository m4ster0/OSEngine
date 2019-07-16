#pragma once

#include "OSE/Math/Geometry/Geometry.h"
#include "OSE/Math/Vector.h"

namespace OSE {

    class PlaneBuilder: public GeometryBuilder
    {
    public:
        PlaneBuilder(std::size_t numSegmentX = 1, std::size_t numSegmentY = 1);

        Geometry build() override;
    private:
        std::size_t m_SegX;
        std::size_t m_SegY;
    };

}