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
        for (auto component : m_Components){
            component.second->OnUpdate(dt);
        }
    }

    void SceneObject::OnFixedUpdate(float dt) {

        if(m_Scene == nullptr){
            return;
        }

        // Update all components of this object
        for (auto component : m_Components){
            component.second->OnFixedUpdate(dt);
        }
    }

    void SceneObject::OnDestroy() {
        if(m_Scene == nullptr){
            return;
        }

        // Remove all components of this object
        for (auto component : m_Components){
            component.second->OnRemove();
        }
    }

    const std::string SceneObject::ToString() {
        return ObjectName;
    }
} // DuckEngine