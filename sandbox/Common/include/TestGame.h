#pragma once

#include <OSE/Graphics/GLRenderer.h>
#include <OSE/Game.h>
#include <OSE/TypeDefs.h>

#include <memory>

struct TriangleData
{
    OSE::GLVertexDescriptor desc{ {{ OSE::GLVertexAttribute::Type::Position, 2 }, { OSE::GLVertexAttribute::Type::Color, 3 }} };
    std::unique_ptr<OSE::GLVertexBuffer> vertices;
    std::unique_ptr<OSE::GLIndexBuffer> indices;
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
    std::unique_ptr<OSE::GLRenderer> renderer{ nullptr };

    //material
    //textures
    std::unique_ptr<OSE::GLProgram> shader{ nullptr };
    //material end
    TriangleData triangleData1;
    TriangleData triangleData2;
};