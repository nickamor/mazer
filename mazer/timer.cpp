//
// Created by Nicholas Amor on 23/10/16.
//

#include "timer.h"

using namespace std::chrono;

void Timer::start() {
    startTime = high_resolution_clock::now();
}

void Timer::stop() {
    stopTime = high_resolution_clock::now();
}

double Timer::time() const {
    double t;
    auto ms = duration_cast<milliseconds>(stopTime - startTime);
    return t;
}