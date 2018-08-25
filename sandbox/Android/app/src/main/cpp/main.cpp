#include <OSE/Platform.h>
#include <OSE/Graphics/GLDevice.h>
#include <OSE/System/FileSystem.h>
#include <OSE/System/File.h>
#include <OSE/System/FileDiskDevice.h>
#include <OSE/Log.h>

#include <TestGame.h>

#include <memory>
#include <string>

int main(int argc, char** argv)
{
    OSE::ConsoleLogSink consoleSink;
    OSE::Logger::AddSink(consoleSink);

    OSE::FileSystem fileSystem{ };
//    OSE::FileDiskDevice diskDevice{ };
//    fileSystem.Mount(diskDevice);

    std::unique_ptr<OSE::File> file = fileSystem.OpenFileSync("assets", "Shaders/default.glsl.shader", OSE::FileMode::Read);
    std::string fileContent;
    if(file != nullptr && file->Read(fileContent))
    {
        //do something with string
        OSE_DEBUG("string content: \n", fileContent.c_str());
    }

    OSE::Platform platform{ std::make_unique<TestGame>(), std::make_unique<OSE::GLDevice>() };

    return platform.Run();
}
