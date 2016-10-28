//
// Created by david on 10/5/2016.
//

#ifndef SKILLED_EAGLE_IR_SENSOREN_HPP
#define SKILLED_EAGLE_IR_SENSOREN_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "DisplayController.hpp"

#define RESOLUTION 1200 //200
#define MAXPULSE 10
#define MINPULSE 2
#define debug 0

class IRReceiver : public rtos::task<> {
    int pulses[100][2];
    int currentpulse = 0;
    int highpulse, lowpulse;
    hwlib::pin_in &tsop_signal;
    rtos::timer interval;

    DisplayController &display;

    void printpulses();

    void main();

public:
    IRReceiver(hwlib::pin_in &tsop_signal, unsigned int priority, const char *name, DisplayController &display) :
            task(priority, name),
            tsop_signal(tsop_signal),
            interval(this, "IRReceiver_interval"),
            display(display) {};

};


#endif //SKILLED_EAGLE_IR_SENSOREN_HPP
