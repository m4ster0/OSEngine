#pragma once
#include "OSE/System/LogSink.h"

#include <string>

namespace OSE {

    class ConsoleLogSink : public LogSink
    {
    public:
        virtual void error(const std::string& msg) override;
        virtual void warning(const std::string& msg) override;
        virtual void info(const std::string& msg) override;
        virtual void debug(const std::string& msg) override;
    };

}