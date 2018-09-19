#include "OSE/System/Logger.h"

namespace OSE {

    Logger::Logger() { }
    Logger::~Logger() { }

    void Logger::LogInternal(LogLevel level, const std::string & msg)
    {
        switch (level)
        {
        case LogLevel::LEVEL_ERROR:
            for (LogSink& sink : m_Sinks)
                sink.error(msg);
            break;
        case LogLevel::LEVEL_WARNING:
            for (LogSink& sink : m_Sinks)
                sink.warning(msg);
            break;
        case LogLevel::LEVEL_INFO:
            for (LogSink& sink : m_Sinks)
                sink.info(msg);
            break;
        case LogLevel::LEVEL_DEBUG:
            for (LogSink& sink : m_Sinks)
                sink.debug(msg);
            break;
        }
    }

    void Logger::AddSinkInternal(LogSink& sink)
    {
        m_Sinks.push_back(std::reference_wrapper<LogSink>(sink));
    }
}