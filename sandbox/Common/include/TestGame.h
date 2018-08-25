#pragma once

#include <OSE/Graphics/GLProgram.h>
#include <OSE/Game.h>
#include <OSE/TypeDefs.h>

#include <memory>

struct TriangleData
{
    OSE::uint vbo;
    OSE::uint ibo;
    OSE::uint vao;
    std::unique_ptr<OSE::GLProgram> shader;
    OSE::uint positionLoc;
    OSE::uint colorLoc;
};

class TestGame: public OSE::Game
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

    TriangleData triangleData1;
    TriangleData triangleData2;


};