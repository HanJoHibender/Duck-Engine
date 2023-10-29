//
// Created by VrikkaDev on 29/10/2023.
//

#ifndef DUCKEXAMPLE_SCENETHREAD_H
#define DUCKEXAMPLE_SCENETHREAD_H

#include "Thread.h"
#include "Scene/Scene.h"

namespace DuckEngine {

    class SceneThread : public Thread {
    public:
        explicit SceneThread(Scene& scene);

        void run() override;
    private:
        Scene& m_Scene;
    };

} // DuckEngine

#endif //DUCKEXAMPLE_SCENETHREAD_H
