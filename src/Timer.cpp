#include <FEngine/Timer.hpp>

Timer::Timer(){
    restart();
}

float Timer::restart(){
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> dur = end - start;
    start = end;
    return dur.count();
}

float Timer::getElapsedTime(){
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> dur = end - start;
    return dur.count();
}