// Bodak_Pavel_SITR.cpp 
//

#include "Tests.h"
#include <iostream>
#include <chrono>

int main()
{
    srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    setlocale(LC_ALL, "Russian");

    std::cout << "задача 1" << std::endl;
    intToBinStrTests();
    
    std::cout << std::endl;
    std::cout << "задача 2" << std::endl;
    serializationTest();
    
    std::cout << std::endl;
    std::cout << "задача 3" << std::endl;
    averageNormalTest();
}