// Bodak_Pavel_SITR.cpp 
//

#include "Tests.h"
#include <iostream>
#include <chrono>

int main()
{
    srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

    // задача 1
    intToBinStrTests();
    // задача 2
    serializationTest();
    // задача 3
    averageNormalTest();

}