#pragma once

#include <string>

namespace OSE {

    class LogSink
    {
    public:
        virtual ~LogSink() { }

        virtual void error(const std::string& msg) = 0;
        virtual void warning(const std::string& msg) = 0;
        virtual void info(const std::string& msg) = 0;
        virtual void debug(const std::string& msg) = 0;
    };

}