#pragma once

#include <OSE/Events/Event.h>

#include <OSE/TypeDefs.h>

namespace OSE {

    struct MouseEvent : public Event
    {
        uint x;
        uint y;
    };

    struct MouseMoveEvent : public MouseEvent { };

    struct MouseButtonEvent : public MouseEvent
    {
        enum class Button
        {
            Left,
            Right,
            Middle
        };

        Button button;
    };

    struct MouseButtonDownEvent : public MouseButtonEvent {};
    struct MouseButtonUpEvent: public MouseButtonEvent {};

    struct KeyboardEvent : public Event
    {
        enum class Key
        {
            1,
            2,
            3,
            4,
            5,
            6,
            7,
            8,
            9,
            0,
            KeyA
        };

        Key key;
        bool altMod;
        bool shiftMod;
        bool ctrlMod;
    };

    struct KeyDownEvent : public KeyboardEvent { };
    struct KeyUpEvent : public KeyboardEvent { };

}