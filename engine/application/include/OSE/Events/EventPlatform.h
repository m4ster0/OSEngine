#pragma once

#include <OSE/Events/Event.h>

namespace OSE {

    struct PlatformResumeEvent : public Event { };
    struct PlatformPauseEvent : public Event { };

}