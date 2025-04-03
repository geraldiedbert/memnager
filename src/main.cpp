#include <iostream>
#include <stdio.h>
#include <random>
#include <array>

using namespace std;

float GetVoltage() {
    std::random_device rd{}; // we initialize the nondeterministic RNG
    std::mt19937 gen{rd()}; // seed the PRNG with rd, just once, so that the seed is truly random

    std::normal_distribution<float> normal(3.6f, 0.3f); // use the PRNG to generate the normal disb.
    return normal(gen);
};

float GetCurrent() {
    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::normal_distribution<float> normal(3.0f, 0.5f);
    return normal(gen);
};

float GetTemperature() {
    std::random_device rd{};
    std::mt19937 gen{rd()};

    float mean = 25.0f;
    float phi = 0.9f;
    float std_dev = 0.1f;

    std::normal_distribution<float> noise(0.0f, std_dev);
    float c = mean * (1.0f - phi);
    float eps =  noise(gen);
    return (c + phi * mean + eps);

};



// basic struct for telemetry data
struct TelemetryData {
    float voltage;
    float current;
    float temperature;
    uint32_t timestamp;

};


// int main() {
//     MemoryManager mm(1024); // create a 1KB memory pool
//     std::cout << "memnager initialized" << std::endl;
//     return 0;
// }

class TelemetryPool {
private:
    void* memoryBlock;
    size_t poolSize;
    size_t blockSize;
    size_t totalBlocks;
    size_t usedBlocks;
 
    // safety features
    uint32_t checkPattern;
    bool isInitialized;

    // Monitoring
    uint32_t peakUsage;
    uint32_t allocFailures;

    // helper functions
    bool validateAddress(void* ptr);
    bool checkMemoryCorruption();

public:
    // core functions
    TelemetryPool(size_t totalSize, size_t blockSize) {
        this->blockSize = blockSize;
        if (totalSize == 0 || blockSize == 0 || blockSize > totalSize) {
            throw std::invalid_argument("invalid pool parameters");
        };
        if (totalSize % blockSize != 0) {
            throw std::invalid_argument("memory block size must be exact multiple of total size");
        }
        this->totalBlocks = totalSize / blockSize;
        this->poolSize = totalSize;
        this->usedBlocks = 0;

        memoryBlock = malloc(this->poolSize);
        
        std::cout << "created " << totalBlocks << " memory blocks of size " << blockSize << "MB" << endl;
        isInitialized = (memoryBlock != nullptr);
    };

    TelemetryData* allocate() {
        if (!isInitialized || usedBlocks >= totalBlocks) {
            return nullptr;
        };
        TelemetryData* block = static_cast<TelemetryData*>(memoryBlock) + (usedBlocks * blockSize);
        usedBlocks++;
        return block;
    };

    // void* deallocate();
    ~TelemetryPool() {
        if (memoryBlock){
            free(memoryBlock); // how can this remove the entire block?
            memoryBlock = nullptr;
            isInitialized = false;
            usedBlocks = 0;
        }
    }

    // status functions
    // bool isFull() const;
    // size_t getFreeSpace() const;
    // uint32_t getUsedBlocks() const;
        
};

int main() {
    TelemetryPool pool1(200, 5); //assigns 1024 bytes, memory block is the start, poolsize is the size
    TelemetryPool pool2(200, 5);
    
    cout << "it works!" << endl;

    cout << "voltage is: " << GetVoltage() << endl; 
    cout << "voltage is: " << GetCurrent() << endl; 
    cout << "voltage is: " << GetTemperature() << endl; 

    // // Get a block?
    // TelemetryPool pool(100);

    // TelemetryData* data1 = pool1.allocate();
    // if (data1) {
    //     data1->voltage = 

    // }

    // sendData(TelemetryData);
    // wait(10); // wait 10 seconds
    // repeat();
    return 0;
    // but do we just reallocate memory?
};