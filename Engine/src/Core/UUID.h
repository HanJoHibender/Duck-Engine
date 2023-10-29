//
// Created by VrikkaDev on 29/10/2023.
//

#ifndef DUCKEXAMPLE_UUID_H
#define DUCKEXAMPLE_UUID_H

#include <iostream>
#include <random>
#include <array>
#include <iomanip>

namespace DuckEngine {

    class UUID {
    public:
        UUID();
        explicit UUID(const std::array<uint32_t, 4>& uintArray);
        UUID(const UUID&) = default;

        explicit operator std::array<uint32_t, 4>() const { return m_Segments; }
        explicit operator std::string() const {
            std::stringstream ss;
            ss << std::hex << std::setfill('0');
            for (int i = 0; i < 4; i++) {
                ss << std::setw(8) << m_Segments[i];
            }
            return ss.str(); }

        bool operator==(const UUID& other) const {
            return m_Segments == other.m_Segments;
        }
        bool operator!=(const UUID& other) const {
            return !(*this == other);
        }
    private:
        std::array<uint32_t, 4> m_Segments;
    };

} // DuckEngine

#endif //DUCKEXAMPLE_UUID_H
