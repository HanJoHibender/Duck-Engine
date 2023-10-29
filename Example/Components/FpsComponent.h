//
// Created by VrikkaDev on 29/10/2023.
//

#ifndef DUCKEXAMPLE_FPSCOMPONENT_H
#define DUCKEXAMPLE_FPSCOMPONENT_H

#include "Engine.h"

class FpsComponent : public DuckEngine::Component{
public:
    FpsComponent();

    void OnUpdate(float dt) override;

    float GetFps() const{
        return m_Fps;
    }
private:
    int m_FrameCount;
    float m_TotalTime, m_Fps;
};


#endif //DUCKEXAMPLE_FPSCOMPONENT_H
