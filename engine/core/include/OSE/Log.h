#pragma once

#include "OSE/System/ConsoleLogSink.h"
#include "OSE/System/Logger.h"

#define OSE_LOG_LEVEL_ERROR 0
#define OSE_LOG_LEVEL_WARNING 1
#define OSE_LOG_LEVEL_INFO 2
#define OSE_LOG_LEVEL_DEBUG 3

#ifndef OSE_LOG_LEVEL
#define OSE_LOG_LEVEL OSE_LOG_LEVEL_DEBUG
#endif

#if OSE_LOG_LEVEL >= OSE_LOG_LEVEL_ERROR
    #define OSE_ERROR(...) OSE::Logger::Log(OSE::LogLevel::LEVEL_ERROR, "OSE: ", __VA_ARGS__)
#else
    #define OSE_ERROR(...)
#endif

#if OSE_LOG_LEVEL >= OSE_LOG_LEVEL_WARNING
    #define OSE_WARN(...) OSE::Logger::Log(OSE::LogLevel::LEVEL_WARNING, "OSE: ", __VA_ARGS__)
#else
    #define OSE_WARN(...)
#endif

#if OSE_LOG_LEVEL >= OSE_LOG_LEVEL_INFO
    #define OSE_INFO(...) OSE::Logger::Log(OSE::LogLevel::LEVEL_INFO, "OSE: ", __VA_ARGS__)
#else
    #define OSE_INFO(...)
#endif

#if OSE_LOG_LEVEL >= OSE_LOG_LEVEL_DEBUG
    #define OSE_DEBUG(...) OSE::Logger::Log(OSE::LogLevel::LEVEL_DEBUG, "OSE: ", __VA_ARGS__)
#else
    #define OSE_DEBUG(...)
#endif

#ifdef DEBUG_OSE
    #define OSE_ASSERT(condition, ...) \
                    if(!(condition)) { \
                        OSE_ERROR("====Assert Failure===="); \
                        OSE_ERROR(__FILE__, ": ", __LINE__); \
                        OSE_ERROR(__VA_ARGS__); \
                    }
#else
    #define OSE_ASSERT(condition, ...)
#endif // DEBUG_OSE
