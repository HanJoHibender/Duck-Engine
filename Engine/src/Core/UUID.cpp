//
// Created by VrikkaDev on 29/10/2023.
//

#include "UUID.h"

namespace DuckEngine {
    UUID::UUID() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint32_t> dis(0, UINT32_MAX);

        for (int i = 0; i < 4; i++) {
            m_Segments[i] = dis(gen);
        }
    }

    UUID::UUID(const std::array<uint32_t, 4>& uintArray) {
        this->m_Segments = uintArray;
    }
} // DuckEngine