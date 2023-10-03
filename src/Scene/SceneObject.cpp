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

        m_Scene->objectRegistry.view<Component>().each([dt](auto object, Component& component){
           component.OnUpdate(dt);
        });
    }
} // DuckEngine