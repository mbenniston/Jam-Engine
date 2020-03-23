#pragma once

#include <chrono>
#include <cmath>

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start, m_end;
public:

    void start() {
        m_start = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        m_end = std::chrono::high_resolution_clock::now();
    }

    //in milliseconds
    double getTime() const {
        std::chrono::duration timeTaken = m_end-m_start;
        return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(timeTaken).count() * powf(10, -6);
    }

};