#include "OSE/Math/Geometry/Geometry.h"

namespace OSE {

    GeometryBuilder& GeometryBuilder::color(ColorGen colorGenerator)
    {
        m_ColorGenerator = colorGenerator;
        return *this;
    }

    GeometryBuilder& GeometryBuilder::uv()
    {
        m_UV = true;
        return *this;
    }

    GeometryBuilder& GeometryBuilder::normals()
    {
        m_Normals = true;
        return *this;
    }
}