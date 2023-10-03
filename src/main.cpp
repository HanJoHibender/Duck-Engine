//
// Created by VrikkaDev on 26/09/2023.
//

#include "Event/Event.h"
#include "Event/WindowEvent.h"

int main(){

    auto we = DuckEngine::WindowEvent(nullptr, 123, 456);

    DuckEngine::EventDispatcher::DispatchEvent(&we);

    return 0;
}