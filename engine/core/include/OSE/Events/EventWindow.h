#pragma once

#include <OSE/Events/Event.h>

namespace OSE {

    struct WindowFocusEvent : public Event
    {
        bool focused;

        WindowFocusEvent(bool f): focused{ f } {}
    };

    struct WindowResizeEvent : public Event
    {
        using uint = unsigned int;
        uint width;
        uint height;

        WindowResizeEvent(uint w, uint h): width{ w }, height{ h } {}
    };
}