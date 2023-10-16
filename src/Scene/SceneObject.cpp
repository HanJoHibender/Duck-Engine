//
// Created by VrikkaDev on 02/10/2023.
//

#include "SceneObject.h"
#include "Components/Component.h"

namespace DuckEngine {
    void SceneObject::OnUpdate(float dt) {

        if(m_Scene == nullptr){
            return;
        }

        // Update all components of this object
        m_Scene->objectRegistry.view<Component>().each([dt](auto object, Component& component){
           component.OnUpdate(dt);
        });
    }

    void SceneObject::OnDestroy() {
        if(m_Scene == nullptr){
            return;
        }

        // Remove all components of this object
        m_Scene->objectRegistry.view<Component>().each([](auto object, Component& component){
            component.OnRemove();
        });
        delete this;
    }
} // DuckEngine