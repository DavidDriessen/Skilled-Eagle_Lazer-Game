//
// Created by david on 10/28/2016.
//

#ifndef SKILLED_EAGLE_DISPLAYCONTROLLER_H
#define SKILLED_EAGLE_DISPLAYCONTROLLER_H

#include "hwlib.hpp"
#include "rtos.hpp"

class DisplayController : public rtos::task<> {
    rtos::timer interval;
    rtos::channel<char *, 1024> data;

    void main();

public:
    DisplayController(unsigned int priority, const char *name) :
            task(priority, name),
            interval(this, "DisplayController_interval"),
            data(this, "Displaybuffer") {};

    void test(char *c);
    void ir(int **pulses, int currentpulse);
};

#endif //SKILLED_EAGLE_DISPLAYCONTROLLER_H
