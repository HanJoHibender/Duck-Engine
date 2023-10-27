//
// Created by VrikkaDev on 02/10/2023.
//

#include "Component.h"
#include "Scene/SceneObject.h"

namespace DuckEngine {
    const std::string Component::ToString() {
        if(m_ParentObject == nullptr){
            return ComponentName;
        }

        return m_ParentObject->ToString() + ": " + ComponentName;
    }
} // DuckEngine