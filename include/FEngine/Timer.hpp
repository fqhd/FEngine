#pragma once
#include <chrono>

namespace FEngine
{
    class Timer
    {
    public:
        Timer();
        float restart();
        float getElapsedTime();

    private:
        std::__1::chrono::steady_clock::time_point start;
    };
}