//
// Created by VrikkaDev on 29/10/2023.
//

#ifndef DUCKEXAMPLE_RENDERTHREAD_H
#define DUCKEXAMPLE_RENDERTHREAD_H

#include "Thread.h"

namespace DuckEngine {

    class RenderThread : public Thread {
    public:
        RenderThread();

        void run() override;
    };

} // DuckEngine

#endif //DUCKEXAMPLE_RENDERTHREAD_H
