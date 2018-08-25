#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory>

namespace OSE {

    template<typename F>
    class Signal;

    template<typename... Args>
    class Signal<void(Args...)>
    {
        using Call = void(*)(void*, Args...);

        template<class C, void(C::*func)(Args...)>
        static void Stub(void* ptr, Args... args)
        {
            (static_cast<C*>(ptr)->*func)(args...);
        }

        struct Callback
        {
            void* instance;
            Call call;

            Callback(void* i, Call c) : instance{ i }, call{ c } {}

            void Apply(Args... args) const { (call)(instance, args...); }
            bool operator==(const Callback& other) const { return instance == other.instance && call == other.call; }
        };

    public:
        template<class C, void(C::*F)(Args...)>
        void Add(C* instance)
        {
            Callback callback{ instance, &Stub<C, F> };
            auto it = std::find(m_Callbacks.begin(), m_Callbacks.end(), callback);
            if (it == m_Callbacks.end())
                m_Callbacks.push_back(std::move(callback));
        }

        template<class C, void(C::*F)(Args...)>
        void Remove(C* instance)
        {
            Callback callback{ instance, &Stub<C, F> };
            auto it = std::find(m_Callbacks.begin(), m_Callbacks.end(), callback);
            if (it != m_Callbacks.end())
                m_Callbacks.erase(it);
        }

        void Invoke(Args... args) const
        {
            for (const Callback& call : m_Callbacks)
                call.Apply(args...);
        }

        std::size_t Size() const { return m_Callbacks.size(); }

    private:
        std::vector<Callback> m_Callbacks;

    };

}