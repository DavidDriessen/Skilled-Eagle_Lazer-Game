//
// Created by david on 10/5/2016.
//

#ifndef SKILLED_EAGLE_IR_ZENDER_HPP
#define SKILLED_EAGLE_IR_ZENDER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class IR_Zender : public rtos::task<> {
    hwlib::pin_out &ir;
    rtos::timer interval;
    void main();

public:
    IR_Zender(hwlib::pin_out &ir, unsigned int priority, const char *name) :
            task(priority, name),
            ir(ir),
            interval(this, "ir_interval") {};

};


#endif //SKILLED_EAGLE_IR_ZENDER_HPP
