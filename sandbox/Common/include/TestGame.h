#pragma once

#include <OSE/Graphics/ResourceID.h>
#include <OSE/Graphics/GraphicsDevice.h>
#include <OSE/Graphics/GraphicsRenderer.h>

#include <OSE/Game.h>
#include <OSE/TypeDefs.h>

#include <memory>

struct Material
{
    OSE::ProgramHandle program;
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
};