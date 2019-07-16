#pragma once

#include "OSE/Events/EventInput.h"

#include "OSE/Math/Math.h"

#include <vector>

namespace OSE {

    struct PlatformCommands;

    class Input
    {
    public:
        bool IsKeyDown(KeyboardEvent::Key key) const;
        bool IsMouseButtonDown(MouseButtonEvent::Button button) const;
        const IVec2& GetMousePosition() const;
    private:
        bool m_Keys[1024];
        bool m_MouseButtons[8];

        friend bool handleInputCommands(const PlatformCommands& cmds);
    };

}