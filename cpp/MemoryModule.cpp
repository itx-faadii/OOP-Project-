#include "../headers/MemoryModule.h"
#include <unistd.h>
// setter
void MemoryModule::setBufferSize(int size) {
    this->bufferSize = size;
}

// getters
int MemoryModule::getBufferSize() const {
    return this->bufferSize;
}
bool MemoryModule::isOverflowDetected() const {
    return this->overflowDetected;
}

// methods
void MemoryModule::writeData(const string& input, Logger& logger) {
    cout << "[MEMORY] Writing data to buffer...\n";
    cout.flush();

    data = input;
//buffer size aik meember ha 
    // overflow check — if input is greater then biffer size 
    if ((int)input.length() > bufferSize) {
        overflowDetected = true;

        cout << "[WARNING] Buffer Overflow Detected!\n";
        cout.flush();

        // Log the overflow event
        logger.log("[OVERFLOW] Buffer overflow in MemoryModule!");
        logger.incrementDetectionLevel();
    } else {
        overflowDetected = false;
        cout << "[OK] Data written safely.\n";
        logger.log("[MEMORY] Data written safely to buffer.");
    }
}

bool MemoryModule::detectOverflow() {
    // simple clogic 
    if ((int)data.length() > bufferSize) {
        overflowDetected = true;
        cout << "[ALERT] Overflow condition active!\n";
        return true;
    }
    cout << "[SAFE] No overflow detected.\n";
    return false;
}

void MemoryModule::reset() {
    // visual feedbac trick used here for delay
    cout << "[SYSTEM] Resetting memory";
    cout.flush();
    for (int i = 0; i < 3; i++) {
        #ifdef _WIN32
            _sleep(500);
        #else
            u_sleep(500000);
        #endif
        cout << ".";
        cout.flush();
    }

    data = "";
    overflowDetected = false;
    cout << "\n[SUCCESS] Memory reset complete.\n";
}

void MemoryModule::showMemoryState() {
    cout << "\n==============================\n";
    cout << "     MEMORY MODULE STATUS     \n";
    cout << "==============================\n";
    cout << "Buffer Size    : " << bufferSize << " bytes\n";
    cout << "Data Size      : " << data.length() << " bytes\n";
    cout << "Used           : " << data.length() << "/" << bufferSize << "\n";
    cout << "Overflow       : " << (overflowDetected ? "YES - VULNERABLE" : "NO - SAFE") << "\n";
    cout << "==============================\n";
}
