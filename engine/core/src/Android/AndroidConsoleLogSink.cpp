#include "OSE/System/ConsoleLogSink.h"

#include <android/log.h>

#define TAG "OSE"

namespace OSE {

    void ConsoleLogSink::error(const std::string &msg)
    {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s", msg.c_str());
    }

    void ConsoleLogSink::warning(const std::string &msg)
    {
        __android_log_print(ANDROID_LOG_WARN, TAG, "%s", msg.c_str());
    }

    void ConsoleLogSink::info(const std::string &msg)
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "%s", msg.c_str());
    }

    void ConsoleLogSink::debug(const std::string &msg)
    {
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "%s", msg.c_str());
    }
}