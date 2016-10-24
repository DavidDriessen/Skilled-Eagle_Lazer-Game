//
// Created by david on 10/5/2016.
//

#ifndef SKILLED_EAGLE_IR_SENSOREN_HPP
#define SKILLED_EAGLE_IR_SENSOREN_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#define RESOLUTION 200
#define MAXPULSE 2000 / RESOLUTION
#define MINPULSE 300 / RESOLUTION

class IR_Receiver : public rtos::task<> {
    int pulses[100][2];
    int currentpulse = 0;
    bool debug = 0;
    int highpulse, lowpulse;
    hwlib::pin_in &tsop_signal;
    rtos::timer interval;

    void printpulses();

    void main();

public:
    IR_Receiver(hwlib::pin_in &tsop_signal, unsigned int priority, const char *name) :
            task(priority, name),
            tsop_signal(tsop_signal),
            interval( this, RESOLUTION, "ir_interval")
    {};

};


#endif //SKILLED_EAGLE_IR_SENSOREN_HPP
