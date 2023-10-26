//
// Created by VrikkaDev on 02/10/2023.
//

#ifndef DUCKENGINE_COMPONENT_H
#define DUCKENGINE_COMPONENT_H

#include <utility>

#include "Event/Event.h"

namespace DuckEngine {

    class SceneObject;

    class Component {
    public:

        Component(std::string name) : ComponentName(std::move(name)){}

        // Gets called when component has been added to a sceneobject.
        virtual void OnAttached(SceneObject* object){m_ParentObject = object;}

        // Gets called every entity tick
        virtual void OnUpdate(float dt){}

        // Gets called when this component gets removed from object
        virtual void OnRemove(){}

        virtual void OnEvent(DuckEngine::Event* event){}


        virtual SceneObject* GetObject(){
            return m_ParentObject;
        }

        virtual std::string ToString();
        std::string ComponentName = "Component";

    protected:
        SceneObject* m_ParentObject;
    };

    namespace Components{
        using DuckEngine::Component;
    } // Components

} // DuckEngine

#endif //DUCKENGINE_COMPONENT_H
