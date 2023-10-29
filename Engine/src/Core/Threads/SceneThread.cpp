//
// Created by VrikkaDev on 29/10/2023.
//

#include "SceneThread.h"

namespace DuckEngine {
    SceneThread::SceneThread(Scene& scene) : Thread("SceneThread"), m_Scene(scene){
    }

    void SceneThread::run() {

        // Set maximum amount of updates on scene per second
        const int maxUpdatesPerSecond = 120;
        const std::chrono::milliseconds maxUpdateTime(1000 / maxUpdatesPerSecond);

        auto lastUpdate = std::chrono::high_resolution_clock::now();
        float deltaTime = 0.0f;

        // Exits the loop when scene gets disabled
        while (m_Scene.IsEnabled){
            // Calculate deltatime
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = now - lastUpdate;
            deltaTime = elapsed.count();

            if (elapsed >= maxUpdateTime) {
                lastUpdate = now;

                // Update the scene
                m_Scene.OnUpdate(deltaTime);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
} // DuckEngine