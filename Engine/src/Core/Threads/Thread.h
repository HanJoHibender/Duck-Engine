//
// Created by VrikkaDev on 29/10/2023.
//

#ifndef DUCKEXAMPLE_THREAD_H
#define DUCKEXAMPLE_THREAD_H

#include "pch.hxx"

namespace DuckEngine {

    // Java style thread class.. mm idk

    class Thread {
    public:
        explicit Thread(std::string_view name);

        // Use this method to start the thread
        void Start();

        virtual void run();
    protected:
        std::thread* m_Thread;
        std::string_view m_Name;
    };

} // DuckEngine

#endif //DUCKEXAMPLE_THREAD_H
