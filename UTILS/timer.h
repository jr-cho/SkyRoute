#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

public:
    void start() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    void stop(const char* label) {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        std::cout << label << " took " << duration.count() << " ms" << std::endl;
    }
};

#endif // TIMER_H

