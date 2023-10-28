//
// Created by VrikkaDev on 26/09/2023.
//

#ifndef DUCKENGINE_MODULE_H
#define DUCKENGINE_MODULE_H

#include "pch.hxx"
#include "Event/Event.h"

namespace DuckEngine {

    class Module {
    public:
        Module(const std::string& name = "Module");
        virtual ~Module() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(long ts) {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };

} // DuckEngine

#endif //DUCKENGINE_MODULE_H
