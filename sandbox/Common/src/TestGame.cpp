#include "TestGame.h"

#include <OSE/Platform.h>
#include <OSE/Graphics/GraphicsDevice.h>
#include <OSE/Graphics/GLCommon.h>
#include <OSE/Log.h>
#include <OSE/TypeDefs.h>
#include <OSE/System/FileSystem.h>

#include <string>
#include <iostream>
#include <cmath>
#include <vector>

TestGame::TestGame() {}
TestGame::~TestGame() {}

void TestGame::OnStart()
{
}

void TestGame::OnLoad()
{
    glViewport(0, 0, 800, 480);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.8f, 1.0f);

    OSE::FileSystem fileSystem{ };

    std::string shaderSrc;
    std::unique_ptr<OSE::File> shaderFile = fileSystem.OpenFileSync("assets", "Assets/Shaders/default.glsl.shader", OSE::FileMode::Read);
    if (shaderFile && shaderFile->Read(shaderSrc))
    {
        OSE_DEBUG("Shader source: \n", shaderSrc);
    }

    std::vector<float> positions1 =
    {
        -0.8f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.8f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.2f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.2f, 0.5f, 0.0f, 1.0f, 1.0f
    };

    std::vector<float> positions2 =
    {
        0.2f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.8f, -0.5f, 0.0f, 1.0f, 0.0f
    };

    std::vector<OSE::uint16> indices1 =
    {
        0, 1, 2,
        2, 1, 3
    };

    std::vector<OSE::uint16> indices2 =
    {
        0, 1, 2
    };

#ifdef WIN32
    std::string vertSource = R"vert(
        #version 330 core
        in vec2 aPosition;
        in vec3 aColor;

        out vec3 vColor;

        void main()
        {
            vColor = aColor;
            gl_Position = vec4(aPosition, 0, 1.0);
        }
    )vert";
#else
    std::string vertSource = R"vert(
        attribute vec4 vPosition;

        void main()
        {
            gl_Position = vPosition;
        }
    )vert";
#endif

#ifdef WIN32
    std::string fragSource = R"frag(
        #version 330 core
        out vec4 outColor;

        in vec3 vColor;

        void main()
        {
            outColor = vec4(vColor, 1.0f);
        }
    )frag";
#else
    std::string fragSource = R"frag(
        precision mediump float;

        void main()
        {
            gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
        }
    )frag";
#endif

    renderer = std::make_unique<OSE::GLRenderer>();

    OSE_DEBUG("Creating shader....");
    OSE_DEBUG("Shader created.");

    using ShaderType = OSE::GLShaderDescriptor::Type;
    using VertAttrType = OSE::GLVertexAttribute::Type;

    shader = OSE::GLProgram::Create(shaderSrc);
    triangleData1.vertices = std::make_unique<OSE::GLVertexBuffer>(4, triangleData1.desc.GetByteSize());
    triangleData1.vertices->Write(reinterpret_cast<const OSE::byte*>(&positions1[0]));

    triangleData1.indices = std::make_unique<OSE::GLIndexBuffer>(6);
    triangleData1.indices->Write(reinterpret_cast<const OSE::byte*>(&indices1[0]));

    triangleData2.vertices = std::make_unique<OSE::GLVertexBuffer>(3, triangleData2.desc.GetByteSize());
    triangleData2.vertices->Write(reinterpret_cast<const OSE::byte*>(&positions2[0]));
    //triangleData2.shader = OSE::GLProgram::Create({ {ShaderType::Vertex, vertSource}, {ShaderType::Fragment, fragSource} });
    //PopulateTriangledata(triangleData2, position2, 3, indices2, 3);
}

void TestGame::OnExit()
{
    shader = nullptr;

    triangleData1.vertices = nullptr;
    triangleData1.indices = nullptr;
    //triangleData2.shader = nullptr;
}

void TestGame::OnResume()
{
}
void TestGame::OnPause() {}

void TestGame::OnUpdate(const OSE::GameTime &gameTime)
{
}

void TestGame::OnRender(const OSE::GameTime &gameTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->render(*shader,
        OSE::RenderPrimitive::Triangles,
        triangleData1.desc, *triangleData1.vertices, *triangleData1.indices);

    renderer->render(*shader,
        OSE::RenderPrimitive::Triangles,
        triangleData2.desc, *triangleData2.vertices);
}