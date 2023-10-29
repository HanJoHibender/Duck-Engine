//
// Created by VrikkaDev on 29/10/2023.
//

#include "FpsComponent.h"

FpsComponent::FpsComponent() : Component("FpsComponent"){
}
void FpsComponent::OnUpdate(float dt) {

    m_FrameCount++;
    m_TotalTime += dt;

    if (m_TotalTime >= 1.0f) {
        m_Fps = static_cast<float>(m_FrameCount) / m_TotalTime;

        // Reset for the next second
        m_FrameCount = 0;
        m_TotalTime = 0.0f;
    }
}
