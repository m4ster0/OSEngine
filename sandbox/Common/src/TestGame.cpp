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

TestGame::TestGame() {}
TestGame::~TestGame() {}

//note to myself: add setting viewport on window init

static void PopulateTriangledata(TriangleData& data, float* vert, OSE::size_t vertSize, unsigned int* indices, OSE::size_t indicesSize)
{
    glGenVertexArrays(1, &data.vao);
    glBindVertexArray(data.vao);

    //VBO Wrapper - requires data from program

    glGenBuffers(1, &data.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, data.vbo); //Binding
    glBufferData(GL_ARRAY_BUFFER, 5 * vertSize * sizeof(float), vert, GL_STATIC_DRAW); //UploadingData


    //VertexDescriptor
    //vertexDescriptor::Attribute
    glEnableVertexAttribArray(data.positionLoc);
    glVertexAttribPointer(data.positionLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

    //vertexDescriptor::Attribute
    glEnableVertexAttribArray(data.colorLoc);
    glVertexAttribPointer(data.colorLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (2 * sizeof(float)));

    //VBO Wrapper

    glGenBuffers(1, &data.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);


    glBindVertexArray(0);
}

void TestGame::OnStart() 
{

}

void TestGame::OnLoad()
{
    glViewport(0, 0, 800, 480);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.8f, 1.0f);

    OSE::FileSystem fileSystem{ };

    std::string shaderSrc{ };
    std::unique_ptr<OSE::File> shaderFile = fileSystem.OpenFileSync("assets", "Assets/Shaders/default.glsl.shader", OSE::FileMode::Read);
    if (shaderFile && shaderFile->Read(shaderSrc))
    {
        OSE_DEBUG("Shader source: \n", shaderSrc);
    }

    float positions1[] =
    {
        -0.8f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.8f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.2f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.2f, 0.5f, 0.0f, 1.0f, 1.0f
    };

    float position2[] =
    {
        0.2f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.8f, -0.5f, 0.0f, 1.0f, 0.0f
    };

    unsigned int indices1[] =
    {
        0, 1, 2,
        2, 1, 3
    };

    unsigned int indices2[] =
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

    OSE_DEBUG("Creating shader....");
    OSE_DEBUG("Shader created.");

    using ShaderType = OSE::GLShader::Type;

    triangleData1.shader = OSE::GLProgram::SingleSrcBuilder{ shaderSrc }
        .AddShader(ShaderType::Vertex, "vertex")
        .AddShader(ShaderType::Fragment, "fragment")
        .Create();
    triangleData1.positionLoc = triangleData1.shader->GetAttributeLocation("aPosition");
    triangleData1.colorLoc = triangleData1.shader->GetAttributeLocation("aColor");
    PopulateTriangledata(triangleData1, positions1, 4, indices1, 6);

    triangleData2.positionLoc = 0;
    triangleData2.colorLoc = 1;
    triangleData2.shader = OSE::GLProgram::Builder{ }
        .AddShader(ShaderType::Vertex, vertSource)
        .AddShader(ShaderType::Fragment, fragSource)
        .BindAttribute(0, "aPosition")
        .BindAttribute(1, "aColor")
        .Create();
    PopulateTriangledata(triangleData2, position2, 3, indices2, 3);
}

void TestGame::OnExit()
{
    triangleData1.shader = nullptr;
    triangleData2.shader = nullptr;
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
    triangleData1.shader->Begin();
    glBindVertexArray(triangleData1.vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    triangleData1.shader->End();
    triangleData2.shader->Begin();
    glBindVertexArray(triangleData2.vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    triangleData2.shader->End();
}