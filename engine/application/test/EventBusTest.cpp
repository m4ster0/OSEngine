#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/test/unit_test.hpp>

#include <OSE/Events/EventBus.h>
#include <OSE/Events/Event.h>
#include <OSE/Events/EventWindow.h>

namespace OSE {

    struct WindowInitEvent: Event { };
    struct WindowTermEvent: Event { };
}

struct WindowListener
{
    using uint = unsigned int;
    uint width{ 0 };
    uint height{ 0 };
    bool focused{ false };
    bool init{ false };

    void onResize(const OSE::WindowResizeEvent& event) { width = event.width; height = event.height; }
    void onFocusChange(const OSE::WindowFocusEvent& event) { focused = event.focused; }
    void onInit(const OSE::WindowInitEvent& event) { init = true; }
    void onDestroy(const OSE::WindowTermEvent& event) { init = false; }
};

struct PlatformListener
{
    bool running{ false };

    void onChange(const OSE::WindowFocusEvent& event) { running = event.focused; }
};

BOOST_AUTO_TEST_CASE(EventBusTest)
{
    OSE::EventBus eventBus;
    WindowListener wListener;
    PlatformListener pListener;

    eventBus.Add<OSE::WindowInitEvent, WindowListener, &WindowListener::onInit>(&wListener);
    eventBus.Add<OSE::WindowFocusEvent, WindowListener, &WindowListener::onFocusChange>(&wListener);
    eventBus.Add<OSE::WindowFocusEvent, PlatformListener, &PlatformListener::onChange>(&pListener);

    eventBus.Dispatch(OSE::WindowInitEvent{});
    eventBus.Dispatch(OSE::WindowFocusEvent{ true });

    eventBus.Remove<OSE::WindowFocusEvent, PlatformListener, &PlatformListener::onChange>(&pListener);
    eventBus.Dispatch(OSE::WindowFocusEvent{ false });
}