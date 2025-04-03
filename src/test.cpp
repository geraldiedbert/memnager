#include <iostream>
#include <stdio.h>
#include <typeinfo>
#include <chrono>

using namespace std;

struct DataPoint {
    int data1;
    int data2;

};

int main() {
    float temperature = 5.000; // this is an implicit type conversion
    //memoryBlock is the pointer to the start of the memory pool?
    //allocate should return telemetrydata?
    std::cout << typeid(temperature).name() << endl;

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::cout << std::ctime(&now_time) << endl;

    return 0;
};
