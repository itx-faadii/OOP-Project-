#ifndef MEMORYMODULE_H
#define MEMORYMODULE_H
#include <iostream>
#include <string>
#include <cstdlib>
#include "ActivityLogger.h"
using namespace std;

class MemoryModule {
private:
    int bufferSize;
    string data;
    bool overflowDetected;

public:
    // constructors
    MemoryModule() : bufferSize(64), data(""), overflowDetected(false) {}
    MemoryModule(int size) : bufferSize(size), data(""), overflowDetected(false) {}
    MemoryModule(const MemoryModule& obj) : bufferSize(obj.bufferSize), data(obj.data), overflowDetected(obj.overflowDetected) {}

    // setters
    void setBufferSize(int size);

    // getters
    int getBufferSize() const;
    bool isOverflowDetected() const;

    // methods
    void writeData(const string& input, Logger& logger);
    bool detectOverflow();
    void reset();
    void showMemoryState();

    ~MemoryModule() {}
};

#endif
