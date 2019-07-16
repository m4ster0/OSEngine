#pragma once

#include <OSE/Events/Event.h>

#include <string>

namespace OSE {

    struct ErrorEvent : public Event
    {
        bool isFatal;
        std::string msg;
    };

}