#include "TestGame.h"

#include <OSE/Platform.h>
#include <OSE/Graphics/GraphicsResourceProxy.h>
#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/Graphics/GLCommon.h>
#include <OSE/Resources/ImageFactory.h>
#include <OSE/Log.h>
#include <OSE/TypeDefs.h>
#include <OSE/System/FileSystem.h>
#include <OSE/Math/Geometry/Cube.h>

#include <string>
#include <iostream>
#include <cmath>
#include <vector>

static OSE::uint texture0;

static void PopulateMesh(OSE::GraphicsResourceProxy& proxy, Mesh& mesh,
    float* vertices, size_t vertSize,
    OSE::uint16* indices = nullptr, size_t indicesSize = 0)
{
    OSE::BufferDescriptor vertexBufferDesc = { vertSize * sizeof(float), vertSize, true };
    OSE::BufferDataDescriptor vertexBufferDataDesc = { reinterpret_cast<const OSE::byte*>(vertices), vertSize * sizeof(float) };
    mesh.vertexBuffer = proxy.CreateBuffer(OSE::BufferType::Vertex, vertexBufferDesc, &vertexBufferDataDesc);

    if (indices && indicesSize)
    {
        OSE::BufferDescriptor indexBufferDesc = { indicesSize * sizeof(OSE::uint16), indicesSize, true };
        OSE::BufferDataDescriptor indexBufferDataDesc = { reinterpret_cast<const OSE::byte*>(indices), indicesSize * sizeof(OSE::uint16) };
        mesh.indexBuffer = proxy.CreateBuffer(OSE::BufferType::Index, indexBufferDesc, &indexBufferDataDesc);
    }
}

TestGame::TestGame() {}
TestGame::~TestGame() {}

void TestGame::OnStart()
{
    view = OSE::Math::translate(OSE::Vec3{ 0.0f, 0.0f, -3.0f });
    projection = OSE::Math::perspective(OSE::Math::toRadians(45.0f), 800.0f / 480.0f, 0.1f, 100.0f);
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



#ifdef WIN32
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
#else
    std::string fragSource = R"frag(
        precision mediump float;

        void main()
        {
            gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
        }
    )frag";
#endif

    std::unique_ptr<OSE::GraphicsResourceProxy> resProxy = OSE::Platform::Instance().GetGraphicsDevice().CreateResourceProxy();

    OSE_DEBUG("Creating shader....");
    std::vector<OSE::ShaderDescriptor> shaderDescs = OSE::shaderDescriptorsFromSource(shaderSrc);
    OSE::ProgramHandle programHandle = resProxy->CreateProgram(shaderDescs);
    OSE_DEBUG("Shader created.");

    material.program = programHandle;

    material.tex0sampler = resProxy->GetProgramUniform<int>(programHandle, "texture0");
    material.tex1sampler = resProxy->GetProgramUniform<int>(programHandle, "texture1");
    material.timeUniform = resProxy->GetProgramUniform<float>(programHandle, "time");
    material.modelUniform = resProxy->GetProgramUniform<OSE::Mat4>(programHandle, "model");
    material.viewUniform = resProxy->GetProgramUniform<OSE::Mat4>(programHandle, "view");
    material.projUniform = resProxy->GetProgramUniform<OSE::Mat4>(programHandle, "projection");

    std::unique_ptr<OSE::Image> image{ nullptr };
    image = OSE::ImageFactory::decode(fileSystem, "assets", "Assets/Textures/container.jpg", { OSE::Image::Format::RGB, false });
    if (image)
    {
        OSE::TextureDescriptor texDesc{};
        material.tex0 = resProxy->CreateTexture(texDesc, image.get());
        image->Dispose();
    }

    image = OSE::ImageFactory::decode(fileSystem, "assets", "Assets/Textures/awesomeface.png", { OSE::Image::Format::RGBA, true });
    if (image)
    {
        OSE::TextureDescriptor texDesc{};
        material.tex1 = resProxy->CreateTexture(texDesc, image.get());
        image->Dispose();
    }

    float positions1[] =
    {
        -1.0f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };

    constexpr size_t positions1Count = sizeof(positions1) / sizeof(positions1[0]);

    std::vector<float> positions2 =
    {
        -0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -0.25f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
        0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
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

    std::vector<OSE::VertexAttributeDescriptor> attrDescs = { {OSE::VertexAttrType::Position, 3}, {OSE::VertexAttrType::Normal, 3}, {OSE::VertexAttrType::TexCoord0, 2} };
    OSE::VertexLayoutHandle vertLayout = resProxy->CreateVertexLayout(attrDescs);

    OSE::Geometry cubeGeometry = OSE::CubeBuilder()
        .normals()
        .uv()
        .build();

    cube.layout = vertLayout;
    PopulateMesh(*resProxy, cube, &cubeGeometry.vertices[0], cubeGeometry.vertices.size(), &cubeGeometry.indices[0], cubeGeometry.indices.size());
    resProxy->GroupVertices(cube.layout, cube.vertexBuffer, cube.indexBuffer);
    //triangle1.layout = vertLayout;
    //PopulateMesh(*resProxy, triangle1, positions1, positions1Count, &indices1[0], indices1.size());

    //triangle2.layout = vertLayout;
    //PopulateMesh(*resProxy, triangle2, &positions2[0], positions2.size());

    //resProxy->GroupVertices(triangle1.layout, triangle1.vertexBuffer, triangle1.indexBuffer);


    renderer = OSE::Platform::Instance().GetGraphicsDevice().CreateRenderer();

    //Sprite sprite
    //Font font
    //ImageLoader imgLoader{ fileSystem };

    //TextureDescriptor
    //{
    //  format = RGB565, RGB888, RGBA8888 itp
    //}
    //Image someImg = imgLoader.load(device, path);
    //promise<Image> someImg = imgLoader.loadAsync(device, path);
    //TextureHandle handle = resProxy->CreateTexture(someImg, textureDescriptor);

    //Material
    //shader

    //RenderCommandBuffer renderCmdBuffer = GraphicsDevice()->CreateRenderCommandBuffer();

    //DrawCall& call = renderCmdBuffer->CreateDrawCall(shaderRID, primitive, layout, vboRID);
    //call.programUniforms = drawSpecificUniforms;
    //call.blendFunction = funcOverrideingDefaultForThisCall;
    //renderCmdBuffer->Queue(call); //sorted internally
    //renderCmdBuffer->Sort();
    //GraphicsDevice()->Flush(renderCmdBuffer);

    //renderer = std::make_unique<OSE::GLRenderer>();
}

void TestGame::OnExit()
{
    //shader = nullptr;

    //triangleData1.vertices = nullptr;
    //triangleData1.indices = nullptr;
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

    float gameTimeSecs = (float) gameTime.total.Seconds();
    OSE::Mat4 translate = OSE::Math::translate(OSE::Vec3{ 1.0f, 0, 0 });
    OSE::Mat4 rotate = OSE::Math::rotate(OSE::Math::toRadians(50.0f) * gameTimeSecs, OSE::Vec3{ 1.0f, 1.0f, 1.0f });

    renderer->BindProgram(material.program);
    renderer->BindTexture(material.tex0, 0);
    renderer->BindTexture(material.tex1, 1);

    material.viewUniform->Bind(view);
    material.projUniform->Bind(projection);

    //pass renderer to check for currently bound program or leave it for user?
    material.tex0sampler->Bind(0);
    material.tex1sampler->Bind(1);
    //material.timeUniform->Bind((float)gameTime.total.Seconds());
    material.modelUniform->Bind(rotate);
    renderer->DrawIndexed(cube.layout, OSE::RenderPrimitive::Triangles,
        cube.vertexBuffer, cube.indexBuffer);

    //renderer->DrawIndexed(triangle1.layout, OSE::RenderPrimitive::Triangles,
    //    triangle1.vertexBuffer, triangle1.indexBuffer);
    //material.transformUniform->Bind(OSE::Mat4{});
    //renderer->Draw(triangle2.layout, OSE::RenderPrimitive::Triangles,
    //    triangle2.vertexBuffer);
}