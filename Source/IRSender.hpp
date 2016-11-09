//
// Created by david on 10/5/2016.
//

#ifndef SKILLED_EAGLE_IR_ZENDER_HPP
#define SKILLED_EAGLE_IR_ZENDER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Weapons.hpp"

#ifndef IRdebuglevel
#define IRdebuglevel 0
#endif

class IRSender : public rtos::task<> {
    hwlib::pin_out &ir;
    rtos::timer interval;
    unsigned char streamA;
    unsigned char streamB;
    bool send[16];
    void main();

public:
    IRSender(hwlib::pin_out &ir, unsigned int priority, const char *name) :
            task(priority, name),
            ir(ir),
            interval(this, "IRSender_interval"),
            streamA(0),
            streamB(0){};

    void fire(int playerId, Weapons wapen);
    void encode_stream(char speler , char data, char control);
    void print_encoded_stream(char a, char b);
    void print_binary(char print, int lenght);
};


#endif //SKILLED_EAGLE_IR_ZENDER_HPP
