#ifndef SANDY_TIME_H
#define SANDY_TIME_H
#include <SFML/Graphics.hpp>
#include <algorithm> //std::clamp as of c++ 17
#include <cmath>     //truncf()

class Time {
private:
    //constants
    static constexpr
    float LOW_LIMIT  = 0.0167f;

    static constexpr
    float HIGH_LIMIT = 1.f;

    static constexpr
    float fps_delay  = 0.2f;

    static inline sf::Clock clock;
    static inline sf::Clock timer;
    static inline float delta_time = LOW_LIMIT;
    static inline float fps        = 0;    //frames per second

public:

    //getters
    static float& getFps()         { return fps; }

    //returns delta time after updating
    static float& getDeltaTime()   {

        delta_time  = clock.restart().asSeconds() * 1000;

        //bounds on delta time
        delta_time = std::clamp(delta_time, LOW_LIMIT, HIGH_LIMIT);

        //update fps based on fps_delay
        if (timer.getElapsedTime().asSeconds() > fps_delay) {
            timer.restart();
            fps = truncf(1000 / delta_time);
        }
        return delta_time;
    }
};


#endif //SANDY_TIME_H
