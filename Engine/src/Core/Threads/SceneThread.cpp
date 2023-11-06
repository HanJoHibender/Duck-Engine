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
        // ((DESIRED_FPS)60/1000)==16.66
        const std::chrono::milliseconds maxFixedUpdateTime(1000 / 60);

        auto lastUpdate = std::chrono::high_resolution_clock::now();
        auto lastFixedUpdate = std::chrono::high_resolution_clock::now();
        float deltaTime, fixedDeltaTime;

        // Exits the loop when scene gets disabled
        while (m_Scene.IsEnabled){
            // Calculate deltatime
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = now - lastUpdate;
            std::chrono::duration<float> elapsedFixed = now - lastFixedUpdate;
            deltaTime = elapsed.count();
            fixedDeltaTime = elapsedFixed.count();

            // Check if enough time has been since last time updated so it caps into maxUpdatesPerSecond
            if (elapsed >= maxUpdateTime) {
                lastUpdate = now;

                // Update the scene
                m_Scene.OnUpdate(deltaTime);
            }

            // Check if enough time has been since last fixedupdate.
            if (elapsedFixed >= maxFixedUpdateTime) {
                lastFixedUpdate = now;

                // Update mouse
                m_Scene.window.input->Update();

                // Update the scene
                m_Scene.OnFixedUpdate(fixedDeltaTime);
            }

            Executor::sceneThreadExecutor.Execute();
        }
    }
} // DuckEngine