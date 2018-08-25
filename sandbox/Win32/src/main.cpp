#include <OSE/Platform.h>
#include <OSE/Graphics/GLDevice.h>
#include <OSE/Log.h>

#include <TestGame.h>

#include <memory>

int main(int argc, char** argv)
{
    OSE::ConsoleLogSink consoleSink;
    OSE::Logger::AddSink(consoleSink);


    // Later Graphics Device will be loaded directly from Window class from some kind of config file via dynamic library, for now it is the way you see
    // TODO create platform settings of some sorts to also pass to platform
    OSE::Platform platform{ std::make_unique<TestGame>(), std::make_unique<OSE::GLDevice>() };

    return platform.Run();
}