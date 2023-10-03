//
// Created by VrikkaDev on 02/10/2023.
//

#ifndef DUCKENGINE_COMPONENT_H
#define DUCKENGINE_COMPONENT_H

namespace DuckEngine {

    class Component {
    public:
        virtual void OnUpdate(float dt){}

        virtual void OnEvent(){}
    };

} // DuckEngine

#endif //DUCKENGINE_COMPONENT_H
