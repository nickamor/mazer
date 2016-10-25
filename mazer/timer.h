//
// Created by Nicholas Amor on 23/10/16.
//

#ifndef MAZER_TIMER_H
#define MAZER_TIMER_H

#include <chrono>

using namespace std::chrono;

class Timer
{
public:
    void start();
    void stop();

    double time() const;

private:
    time_point<std::chrono::high_resolution_clock> startTime, stopTime;

};


#endif //MAZER_TIMER_H
