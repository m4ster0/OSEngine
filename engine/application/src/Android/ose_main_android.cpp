#include "OSE/System/FileSystem.h"
#include "AndroidAssetFileDevice.h"
#include "android_native_app_glue.h"

#include <cstdlib>

extern int main(int argc, char **argv);

extern struct android_app* g_Application;

extern void handle_cmd(struct android_app *application, int32_t cmd);
extern int32_t handle_input(struct android_app *application, AInputEvent *event);

void android_main(struct android_app *application) {
    app_dummy();

    g_Application = application;
    g_Application->onAppCmd = handle_cmd;
    g_Application->onInputEvent = handle_input;

    OSE::AndroidAssetFileDevice assetDevice{ g_Application->activity->assetManager };
    OSE::FileSystem::MountShared(assetDevice);

    //ideally add in main additional disk file resolvers for obb and external storage
    int result = main(0, nullptr);

    exit(result);
}


