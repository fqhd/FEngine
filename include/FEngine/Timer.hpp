#pragma once
#include <chrono>

class Timer {
public:

    Timer();
    float restart();
    float getElapsedTime();

private:

    std::__1::chrono::steady_clock::time_point start;

};