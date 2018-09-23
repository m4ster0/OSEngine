#pragma once

#include <OSE/Graphics/ResourceID.h>
#include <OSE/Graphics/GraphicsDevice.h>
#include <OSE/Graphics/GraphicsRenderer.h>
#include <OSE/Graphics/GraphicsResourceDescriptor.h>
#include <OSE/Graphics/GraphicsProgramUniform.h>
#include <OSE/Math/Math.h>


#include <OSE/Game.h>
#include <OSE/TypeDefs.h>

#include <memory>

struct Material
{
    OSE::TextureHandle tex0;
    OSE::TextureHandle tex1;
    OSE::ProgramHandle program;
    const OSE::ProgramUniform<int>* tex0sampler;
    const OSE::ProgramUniform<int>* tex1sampler;
    const OSE::ProgramUniform<float>* timeUniform;
    const OSE::ProgramUniform<OSE::Mat4>* modelUniform;
    const OSE::ProgramUniform<OSE::Mat4>* viewUniform;
    const OSE::ProgramUniform<OSE::Mat4>* projUniform;
};

struct Mesh
{
    OSE::VertexLayoutHandle layout;
    OSE::BufferHandle vertexBuffer;
    OSE::BufferHandle indexBuffer;
};
class TestGame : public OSE::Game
{

public:
    TestGame();

    ~TestGame();

    virtual void OnStart() override;
    virtual void OnLoad() override;
    virtual void OnExit() override;

    virtual void OnResume() override;
    virtual void OnPause() override;

    virtual void OnUpdate(const OSE::GameTime& gameTime) override;
    virtual void OnRender(const OSE::GameTime& gameTime) override;

private:
    std::unique_ptr<OSE::GraphicsRenderer> renderer{ nullptr };

    Material material;
    Mesh triangle1;
    Mesh triangle2;
    Mesh cube;

    OSE::Mat4 view;
    OSE::Mat4 projection;
};