#include <Windows.h>
#include <iostream>
#include <thread>

class DeltaTime {
public:
    DeltaTime() {
        QueryPerformanceFrequency(&frequency);
        lastTime = GetCurrentTime();
        totalTime = 0.0;
    }

    void Update() {
        long long currentTime = GetCurrentTime();
        deltaTime = static_cast<double>(currentTime - lastTime) / frequency.QuadPart;
        totalTime += deltaTime; // Update total time
        lastTime = currentTime;
    }

    double GetDeltaTime() const {
        return deltaTime;
    }

    double GetTotalTime() const {
        return totalTime;
    }

private:
    long long GetCurrentTime() {
        LARGE_INTEGER time;
        QueryPerformanceCounter(&time);
        return time.QuadPart;
    }

    LARGE_INTEGER frequency;
    long long lastTime;
    double deltaTime = 0.0;
    double totalTime = 0.0; // Store total time
};