#pragma once

#include <OSE/Events/Event.h>
#include <OSE/Events/Signal.h>

#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <memory>

namespace OSE {

    class EventBus
    {
        template<typename E>
        using Assert = std::enable_if<std::is_base_of<Event, E>::value>;

        class EventSignalBase
        {
        public:
            virtual ~EventSignalBase() {};
            virtual void ForwardInvoke(const Event& event) const = 0;
            virtual std::size_t Size() const = 0;
        };

        template<typename E>
        class EventSignal : public EventSignalBase
        {
        public:
            template<class C, void(C::*M)(const E&)>
            void ForwardAdd(C* instance) { m_Signal.template Add<C, M>(instance); }

            template<class C, void(C::*M)(const E&)>
            void ForwardRemove(C* instance) { m_Signal.template Remove<C, M>(instance); }

            virtual void ForwardInvoke(const Event& event) const override {  m_Signal.Invoke(dynamic_cast<const E&>(event)); }

            virtual std::size_t Size() const override { return m_Signal.Size(); }

        private:
            Signal<void(const E&)> m_Signal;
        };

    public:

        template<typename E, class C, void(C::*M)(const E&), typename = Assert<E>>
        void Add(C* instance)
        {
            auto tag = std::type_index(typeid(E));
            auto it = m_EventSignals.find(tag);
            if (it == m_EventSignals.end())
                m_EventSignals[tag] = std::unique_ptr<EventSignalBase>(new EventSignal<E>);

            EventSignal<E>* eventSignal = static_cast<EventSignal<E>*>(m_EventSignals[tag].get());
            eventSignal->template ForwardAdd<C, M>(instance);
        }

        template<typename E, class C, void(C::*M)(const E&), typename = Assert<E>>
        void Remove(C* instance)
        {
            auto tag = std::type_index(typeid(E));
            auto it = m_EventSignals.find(tag);
            if (it != m_EventSignals.end())
            {
                EventSignal<E>* eventSignal = static_cast<EventSignal<E>*>(m_EventSignals[tag].get());
                eventSignal->template ForwardRemove<C, M>(instance);

                if (eventSignal->Size() == 0)
                    m_EventSignals.erase(it);
            }
        }

        void Dispatch(const Event& event)
        {
            auto tag = std::type_index(typeid(event));
            auto it = m_EventSignals.find(tag);
            if (it != m_EventSignals.end())
                m_EventSignals[tag]->ForwardInvoke(event);
        }

//        std::size_t size() const
//        {
//            std::size_t size{ 0 };
//            for (const auto& i : m_EventSignals)
//                size += i.second->Size();
//
//            return size;
//        }
//
//        template<typename E = Assert<E>>
//        std::size_t size() const
//        {
//            std::size_t size{ 0 };
//            auto tag = std::type_index(typeid(E));
//            auto it = m_EventSignals.find(tag);
//            if (it != m_EventSignals.end())
//                size = m_EventSignals[tag]->Size();
//
//            return size;
//        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<EventSignalBase>> m_EventSignals;
    };
}