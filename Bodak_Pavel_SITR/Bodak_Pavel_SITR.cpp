// Bodak_Pavel_SITR.cpp 
//

#include "Tests.h"
#include <iostream>
#include <chrono>

int main()
{
    srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

    // ������ 1
    intToBinStrTests();
    // ������ 2
    serializationTest();
    // ������ 3
    averageNormalTest();

}