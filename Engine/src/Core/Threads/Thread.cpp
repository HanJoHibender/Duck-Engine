//
// Created by VrikkaDev on 29/10/2023.
//

#include "Thread.h"

namespace DuckEngine {
    Thread::Thread(std::string_view name) {
        m_Name = name;
    }

    void Thread::Start() {
        m_Thread = new std::thread(&Thread::run, this);
    }

    void Thread::run() {
    }
} // DuckEngine