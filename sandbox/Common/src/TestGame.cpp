#include "TestGame.h"

#include <OSE/Platform.h>
#include <OSE/Graphics/GraphicsResourceProxy.h>
#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/Graphics/GLCommon.h>
#include <OSE/Resources/ImageFactory.h>
#include <OSE/Log.h>
#include <OSE/TypeDefs.h>
#include <OSE/System/FileSystem.h>

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

    material.tex0sampler = resProxy->GetProgramUniform(programHandle, "texture0");
    material.tex1sampler = resProxy->GetProgramUniform(programHandle, "texture0");

    std::unique_ptr<OSE::Image> image{ nullptr };
    image = OSE::ImageFactory::Decode(fileSystem, "assets", "Assets/Textures/container.jpg", { OSE::Image::Format::RGB, false });
    if (image)
    {
        OSE::TextureDescriptor texDesc{};
        material.tex0 = resProxy->CreateTexture(texDesc, image.get());
        image->Dispose();
    }

    image = OSE::ImageFactory::Decode(fileSystem, "assets", "Assets/Textures/awesomeface.png", { OSE::Image::Format::RGBA, true });
    if (image)
    {
        OSE::TextureDescriptor texDesc{};
        material.tex1 = resProxy->CreateTexture(texDesc, image.get());
        image->Dispose();
    }

    float positions1[] =
    {
        -0.8f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.8f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.2f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.2f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };

    constexpr size_t positions1Count = sizeof(positions1) / sizeof(positions1[0]);

    std::vector<float> positions2 =
    {
        0.2f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
        0.8f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
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

    std::vector<OSE::VertexAttributeDescriptor> attrDescs = { {OSE::VertexAttrType::Position, 2}, {OSE::VertexAttrType::Color, 3}, {OSE::VertexAttrType::TexCoord0, 2} };
    OSE::VertexLayoutHandle vertLayout = resProxy->CreateVertexLayout(attrDescs);

    triangle1.layout = vertLayout;
    PopulateMesh(*resProxy, triangle1, positions1, positions1Count, &indices1[0], indices1.size());

    triangle2.layout = vertLayout;
    PopulateMesh(*resProxy, triangle2, &positions2[0], positions2.size());

    resProxy->GroupVertices(triangle1.layout, triangle1.vertexBuffer, triangle1.indexBuffer);


    renderer = OSE::Platform::Instance().GetGraphicsDevice().CreateRenderer();

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

    ////bind material
    ////set global uniforms and textures
    //float correction1 = (sin(gameTime.total.Seconds() * 2.0) / 2.0) + 0.5;
    //float correction2 = (sin(gameTime.total.Seconds()) / 2.0) + 0.5;
    //shader->Use();
    renderer->BindProgram(material.program);
    renderer->BindTexture(material.tex0, 0);
    renderer->BindTexture(material.tex1, 1);
    renderer->SetProgramUniform(*material.tex0sampler, 0);
    renderer->SetProgramUniform(*material.tex1sampler, 1);

    renderer->DrawIndexed(triangle1.layout, OSE::RenderPrimitive::Triangles,
        triangle1.vertexBuffer, triangle1.indexBuffer);

    renderer->Draw(triangle2.layout, OSE::RenderPrimitive::Triangles,
        triangle2.vertexBuffer);
}