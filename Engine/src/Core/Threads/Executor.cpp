//
// Created by VrikkaDev on 31/10/2023.
//

#include "Executor.h"

namespace DuckEngine {

    Executor Executor::mainThreadExecutor = Executor();
    Executor Executor::sceneThreadExecutor = Executor();

    void Executor::Execute() {
        std::function<void()> task;
        // Check if there's a task in the queue
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (!taskQueue.empty()) {
                task = taskQueue.front();
                taskQueue.pop_back();
            }
        }
        // Execute the task
        if (task) {
            task();
        }
    }
} // DuckEngine