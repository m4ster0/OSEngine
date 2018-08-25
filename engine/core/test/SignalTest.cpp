#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/test/unit_test.hpp>

#include <OSE/Events/Signal.h>

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <iostream>
#include <string>

struct Event
{
    virtual ~Event() {};
    virtual int get() const { return 1; }
};

struct DerivedEvent : public Event
{
    int value;

    DerivedEvent(int v): value{ v } {}

    virtual int get() const override { return value; }
};

struct Listener
{
    int valA{ 0 };
    int valB{ 0 };

    void reset() { valA = valB = 0; }

    void eventFuncA(const Event& event) { valA += event.get(); }
    void eventFuncB(const Event& event) { valB += event.get(); }
    void eventFuncDerived(const DerivedEvent& event) {  };

    void eventFuncMultiA(const Event& event, int mul) { valA += (event.get() * mul); }
    void eventFuncMultiB(const Event& event, int mul) { valB += (event.get() * mul); }
};

BOOST_AUTO_TEST_CASE(SignalEmpty)
{
    OSE::Signal<void(const Event&)> signal;
    BOOST_CHECK(signal.Size() == 0);

    Listener listener;
    BOOST_CHECK(listener.valA == 0);
    BOOST_CHECK(listener.valB == 0);

    listener.valA = 10;
    listener.valB = 10;
    listener.reset();
    BOOST_CHECK(listener.valA == 0);
    BOOST_CHECK(listener.valB == 0);
}

BOOST_AUTO_TEST_CASE(SignalAdd)
{
    OSE::Signal<void(const Event&)> signal;

    Listener listenerA;
    signal.Add<Listener, &Listener::eventFuncA>(&listenerA);
    signal.Add<Listener, &Listener::eventFuncB>(&listenerA);
    BOOST_CHECK(signal.Size() == 2);

    //Duplicate function ignore check
    signal.Add<Listener, &Listener::eventFuncA>(&listenerA);
    BOOST_CHECK(signal.Size() == 2);

    Listener listenerB;
    signal.Add<Listener, &Listener::eventFuncA>(&listenerB);
    signal.Add<Listener, &Listener::eventFuncB>(&listenerB);
    BOOST_CHECK(signal.Size() == 4);
}

BOOST_AUTO_TEST_CASE(SignalRemove)
{
    OSE::Signal<void(const Event&)> signal;

    Listener listenerA;
    Listener listenerB;
    signal.Add<Listener, &Listener::eventFuncA>(&listenerA);
    signal.Add<Listener, &Listener::eventFuncB>(&listenerA);

    //Removing not added functions
    signal.Remove<Listener, &Listener::eventFuncA>(&listenerB);
    signal.Remove<Listener, &Listener::eventFuncB>(&listenerB);
    BOOST_CHECK(signal.Size() == 2);

    signal.Add<Listener, &Listener::eventFuncA>(&listenerB);
    signal.Add<Listener, &Listener::eventFuncB>(&listenerB);

    signal.Remove<Listener, &Listener::eventFuncB>(&listenerA);
    signal.Remove<Listener, &Listener::eventFuncB>(&listenerB);
    BOOST_CHECK(signal.Size() == 2);

    signal.Remove<Listener, &Listener::eventFuncA>(&listenerA);
    signal.Remove<Listener, &Listener::eventFuncA>(&listenerB);
    BOOST_CHECK(signal.Size() == 0);

}

BOOST_AUTO_TEST_CASE(SignalDispatch)
{
    OSE::Signal<void(const Event&)> signal;

    Listener listenerA;
    signal.Add<Listener, &Listener::eventFuncA>(&listenerA);
    signal.Add<Listener, &Listener::eventFuncB>(&listenerA);

    Listener listenerB;
    signal.Add<Listener, &Listener::eventFuncA>(&listenerB);
    signal.Add<Listener, &Listener::eventFuncB>(&listenerB);

    signal.Invoke(Event{});
    BOOST_CHECK(listenerA.valA == 1);
    BOOST_CHECK(listenerA.valB == 1);
    BOOST_CHECK(listenerB.valA == 1);
    BOOST_CHECK(listenerB.valB == 1);

    signal.Invoke(DerivedEvent{ 2 });
    BOOST_CHECK(listenerA.valA == 3);
    BOOST_CHECK(listenerA.valB == 3);
    BOOST_CHECK(listenerB.valA == 3);
    BOOST_CHECK(listenerB.valB == 3);

    signal.Remove<Listener, &Listener::eventFuncB>(&listenerA);
    signal.Remove<Listener, &Listener::eventFuncB>(&listenerB);
    signal.Invoke(DerivedEvent{ 2 });
    BOOST_CHECK(listenerA.valA == 5);
    BOOST_CHECK(listenerA.valB == 3);
    BOOST_CHECK(listenerB.valA == 5);
    BOOST_CHECK(listenerB.valB == 3);

    OSE::Signal<void(const Event&, int)> signalMul;
    signalMul.Add<Listener, &Listener::eventFuncMultiA>(&listenerA);
    signalMul.Add<Listener, &Listener::eventFuncMultiB>(&listenerA);
    signalMul.Invoke(DerivedEvent{ 2 }, 2);
    BOOST_CHECK(listenerA.valA == 9);
    BOOST_CHECK(listenerA.valB == 7);
}