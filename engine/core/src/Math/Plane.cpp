#include "OSE/Math/Geometry/Plane.h"

namespace OSE {

    PlaneBuilder::PlaneBuilder(std::size_t numSegmentX, std::size_t numSegmentY):
        m_SegX{ numSegmentX }, m_SegY{ numSegmentY }
    {
    }

    Geometry PlaneBuilder::build()
    {
        std::size_t vertSize = 3;
        if (m_ColorGenerator != nullptr) vertSize += 3;
        if (m_Normals) vertSize += 3;
        if (m_UV) vertSize += 2;

        std::size_t vertCountX = m_SegX + 1;
        std::size_t vertCountY = m_SegY + 1;

        Geometry plane;
        plane.vertices.reserve(vertCountX * vertCountY * vertSize);
        plane.indices.reserve(m_SegX * m_SegY * 6);

        Vec3 normal = Vec3::ZAxis;

        Vec2 start{ -0.5, -0.5 };
        Vec2 offset{ 1.0f / m_SegX, 1.0f / m_SegY };
        for (std::size_t x = 0; x < vertCountX; ++x)
        {
            for (std::size_t y = 0; y < vertCountY; ++y)
            {
                Vec3 vertex{ start.x + offset.x * x, start.y + offset.y * y, 0 };
                plane.vertices.push_back(vertex.x);
                plane.vertices.push_back(vertex.y);
                plane.vertices.push_back(vertex.z);

                if (m_Normals)
                {
                    plane.vertices.push_back(normal.x);
                    plane.vertices.push_back(normal.y);
                    plane.vertices.push_back(normal.z);
                }

                if (m_ColorGenerator)
                {
                    Vec3 color = m_ColorGenerator(vertex, normal, { 1.0f, 1.0f, 0 });
                    plane.vertices.push_back(color.x);
                    plane.vertices.push_back(color.y);
                    plane.vertices.push_back(color.z);
                }

                if (m_UV)
                {
                    Vec2 uv = vertex.xy + 0.5f;
                    plane.vertices.push_back(uv.x);
                    plane.vertices.push_back(uv.y);
                }

                if (x < vertCountX - 1 && y < vertCountY - 1)
                {
                    plane.indices.push_back(x * vertCountY + y);
                    plane.indices.push_back((x + 1) * vertCountY + y);
                    plane.indices.push_back((x + 1) * vertCountY + y + 1);
                    plane.indices.push_back((x + 1) * vertCountY + y + 1);
                    plane.indices.push_back(x * vertCountY + y + 1);
                    plane.indices.push_back(x * vertCountY + y);
                }
            }
        }

        return plane;
    }
}