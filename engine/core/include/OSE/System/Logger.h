#pragma once

#include "OSE/System/LogSink.h"

#include <vector>
#include <functional>
#include <utility>
#include <string>
#include <sstream>

namespace OSE {

    enum class LogLevel
    {
        LEVEL_DEBUG,
        LEVEL_WARNING,
        LEVEL_INFO,
        LEVEL_ERROR
    };

    //add potentially multithreading safety
    class Logger
    {
    public:
        template<typename... Args>
        static void Log(LogLevel level, Args... args)
        {
            std::stringstream stream;
            LogStream(stream, std::forward<Args>(args)...);
            Log(level, stream.str());
        }

        static void Log(LogLevel level, const std::string& msg)
        {
            Instance().LogInternal(level, msg);
        }

        static void AddSink(LogSink& sink)
        {
            Instance().AddSinkInternal(sink);
        }

    private:

        template<typename Arg>
        static void LogStream(std::stringstream& stream, Arg&& arg)
        {
            stream << arg;
        }

        template<typename First, typename... Rest>
        static void LogStream(std::stringstream& stream, First&& first, Rest&&... rest)
        {
            LogStream(stream, std::forward<First>(first));
            LogStream(stream, std::forward<Rest>(rest)...);
        }

        inline static Logger& Instance()
        {
            static Logger logger;
            return logger;
        }

        Logger();
        ~Logger();

        void LogInternal(LogLevel level, const std::string& msg);
        void AddSinkInternal(LogSink& sink);

        std::vector<std::reference_wrapper<LogSink>> m_Sinks;
    };
}