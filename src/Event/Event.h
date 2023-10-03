//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_EVENT_H
#define DUCKENGINE_EVENT_H

#include "pch.hxx"

namespace DuckEngine {

    class Event {
    public:
        Event() = default;
        ~Event() = default;
        virtual void HandleEvent(Event* event) {}
    protected:
        virtual void RegisterEvents() {}
    };

    class EventDispatcher {
    public:
        // Add a receiver to the list of event receivers.
        static void AddReceiver(Event* eventReceiver) {
            m_EventReceivers.push_back(eventReceiver);
        }

        // Dispatch an event to all registered event receivers.
        static void DispatchEvent(Event* event) {
            for (auto eventReceiver : m_EventReceivers) {
                eventReceiver->HandleEvent(event);
            }
        }

    private:
        inline static std::vector<Event*> m_EventReceivers;
    };

} // DuckEngine

#endif //DUCKENGINE_EVENT_H
