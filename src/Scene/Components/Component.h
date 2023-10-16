//
// Created by VrikkaDev on 02/10/2023.
//

#ifndef DUCKENGINE_COMPONENT_H
#define DUCKENGINE_COMPONENT_H

#include "Event/Event.h"

namespace DuckEngine {

    class Component {
    public:

        // Gets called when component has been added to a entity.
        virtual void OnAttached(){}

        // Gets called every entity tick
        virtual void OnUpdate(float dt){}

        // Gets called when this component gets removed from object
        virtual void OnRemove(){}

        virtual void OnEvent(DuckEngine::Event* event){}
    };

    namespace Components{
        using DuckEngine::Component;
    } // Components

} // DuckEngine

#endif //DUCKENGINE_COMPONENT_H
