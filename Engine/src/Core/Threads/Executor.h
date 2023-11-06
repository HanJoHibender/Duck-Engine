//
// Created by VrikkaDev on 31/10/2023.
//

#ifndef DUCKEXAMPLE_EXECUTOR_H
#define DUCKEXAMPLE_EXECUTOR_H

namespace DuckEngine {

    class Executor {
    public:
        // Submit a function or task to be executed asynchronously
        template <typename Function, typename... Args>
        void Submit(Function&& f, Args&&... args) {
            auto task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
            std::lock_guard<std::mutex> lock(queueMutex);
            taskQueue.push_back(task);
        }

        void Execute();

        static Executor mainThreadExecutor;
        static Executor sceneThreadExecutor;
    private:
        std::vector<std::function<void()>> taskQueue;
        std::mutex queueMutex;
    };

} // DuckEngine

#endif //DUCKEXAMPLE_EXECUTOR_H
