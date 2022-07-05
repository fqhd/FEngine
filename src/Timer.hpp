#pragma once

#include <chrono>

class Timer
{
public:
    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    double restart()
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> deltaTime = now - start;
        start = now;
        return deltaTime.count();
    }

    double getElapsedTime()
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> deltaTime = now - start;
        return deltaTime.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};