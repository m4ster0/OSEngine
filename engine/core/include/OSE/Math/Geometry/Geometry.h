#pragma once

#include "OSE/Math/Vector.h"

#include <vector>

namespace OSE {

    struct Geometry
    {
        std::vector<float> vertices;
        std::vector<std::uint16_t> indices;
    };

    class GeometryBuilder
    {
    public:
        using ColorGen = Vec3(*)(const Vec3& vertex, const Vec3& normals, const Vec3& dimen);

        GeometryBuilder() = default;
        virtual ~GeometryBuilder() = default;

        GeometryBuilder& color(ColorGen colorGenerator);
        GeometryBuilder& uv();
        GeometryBuilder& normals();
        virtual Geometry build() = 0;

    protected:
        ColorGen m_ColorGenerator{ nullptr };
        bool m_UV{ false };
        bool m_Normals{ false };
    };

}