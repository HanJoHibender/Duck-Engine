//
// Created by VrikkaDev on 03/10/2023.
//

#ifndef DUCKENGINE_CONSTANTS_H
#define DUCKENGINE_CONSTANTS_H

#include "uuid_v4/uuid_v4.h"

namespace DuckEngine{

    static UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

} // DuckEngine

#endif //DUCKENGINE_CONSTANTS_H
