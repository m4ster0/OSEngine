#include "OSE/Math/Geometry/Cube.h"

#include "OSE/Math/Math.h"

namespace OSE {

    Geometry CubeBuilder::build()
    {
        std::size_t vertSize = 3;
        if (m_ColorGenerator != nullptr) vertSize += 3;
        if (m_Normals) vertSize += 3;
        if (m_UV) vertSize += 2;

        Geometry cube;
        cube.vertices.reserve(4 * 6 * vertSize);

        auto insertVert = [&cube, this](const Vec3& vertex, const Vec3& normal, const OSE::Vec2& uv) {

            cube.vertices.push_back(vertex.x);
            cube.vertices.push_back(vertex.y);
            cube.vertices.push_back(vertex.z);

            if (m_Normals)
            {
                cube.vertices.push_back(normal.x);
                cube.vertices.push_back(normal.y);
                cube.vertices.push_back(normal.z);
            }

            if (m_ColorGenerator)
            {
                Vec3 color = m_ColorGenerator(vertex, normal, { 1.0f, 1.0f, 1.0f });
                cube.vertices.push_back(color.x);
                cube.vertices.push_back(color.y);
                cube.vertices.push_back(color.z);
            }

            if (m_UV)
            {
                cube.vertices.push_back(uv.x);
                cube.vertices.push_back(uv.y);
            }
        };

        Vec3 normal;
        //front
        normal = Vec3{ 0.0f, 0.0f, 1.0f };
        insertVert({ -0.5f, -0.5f, 0.5f }, normal, { 0.0f, 0.0f });
        insertVert({  0.5f, -0.5f, 0.5f }, normal, { 1.0f, 0.0f });
        insertVert({  0.5f,  0.5f, 0.5f }, normal, { 1.0f, 1.0f });
        insertVert({ -0.5f,  0.5f, 0.5f }, normal, { 0.0f, 1.0f });
        //back
        normal = Vec3{ 0.0f, 0.0f, -1.0f };
        insertVert({ -0.5f, -0.5f, -0.5f }, normal, { 0.0f, 0.0f });
        insertVert({  0.5f, -0.5f, -0.5f }, normal, { 1.0f, 0.0f });
        insertVert({  0.5f,  0.5f, -0.5f }, normal, { 1.0f, 1.0f });
        insertVert({ -0.5f,  0.5f, -0.5f }, normal, { 0.0f, 1.0f });
        //top
        normal = Vec3{ 0.0f, 1.0f, 0.0f };
        insertVert({ -0.5f, 0.5f, -0.5f }, normal, { 0.0f, 0.0f });
        insertVert({  0.5f, 0.5f, -0.5f }, normal, { 1.0f, 0.0f });
        insertVert({  0.5f, 0.5f,  0.5f }, normal, { 1.0f, 1.0f });
        insertVert({ -0.5f, 0.5f,  0.5f }, normal, { 0.0f, 1.0f });
        //bottom
        normal = Vec3{ 0.0f, -1.0f, 0.0f };
        insertVert({ -0.5f, -0.5f, -0.5f }, normal, { 0.0f, 0.0f });
        insertVert({  0.5f, -0.5f, -0.5f }, normal, { 1.0f, 0.0f });
        insertVert({  0.5f, -0.5f,  0.5f }, normal, { 1.0f, 1.0f });
        insertVert({ -0.5f, -0.5f,  0.5f }, normal, { 0.0f, 1.0f });
        //left
        normal = Vec3{ -1.0f, 0.0f, 0.0f };
        insertVert({ -0.5f, -0.5f, -0.5f }, normal, { 0.0f, 0.0f });
        insertVert({ -0.5f, -0.5f,  0.5f }, normal, { 1.0f, 0.0f });
        insertVert({ -0.5f,  0.5f,  0.5f }, normal, { 1.0f, 1.0f });
        insertVert({ -0.5f,  0.5f, -0.5f }, normal, { 0.0f, 1.0f });
        //right
        normal = Vec3{ -1.0f, 0.0f, 0.0f };
        insertVert({ 0.5f, -0.5f,  0.5f }, normal, { 0.0f, 0.0f });
        insertVert({ 0.5f, -0.5f, -0.5f }, normal, { 1.0f, 0.0f });
        insertVert({ 0.5f,  0.5f, -0.5f }, normal, { 1.0f, 1.0f });
        insertVert({ 0.5f,  0.5f,  0.5f }, normal, { 0.0f, 1.0f });

        cube.indices = {
            0, 1, 2, 0, 2, 3, //front
            4, 5, 6, 4, 6, 7, //back
            8, 9, 10, 8, 10, 11, //top
            12, 13, 14, 12, 14, 15, //bottom
            16, 17, 18, 16, 18, 19, //left
            20, 21, 22, 20, 22, 23 //right
        };

        return cube;
    }
}