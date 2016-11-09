//
// Created by MuscioCraft on 7-11-2016.
//

#ifndef SKILLED_EAGLE_KEPPADCONTORLLER_HPP
#define SKILLED_EAGLE_KEPPADCONTORLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "bmptk.h"
#include "InitController.hpp"
#include <stdlib.h>
#include "Weapons.hpp"
#include "DisplayController.hpp"

using namespace hwlib;

class KeyPadController: public rtos::task<>{
private:
    InitController & init;
    hwlib::istream & keypad;
    rtos::timer KeyTimer;
    DisplayController & display;

    void main();

public:
    KeyPadController(unsigned int priority, const char *name, InitController &init, hwlib::istream &pad, DisplayController &display) :
            task(priority, name), init(init), keypad(pad), KeyTimer(this, "KeyPadTimer"),
            display(display) {};

    int array_to_intger(int *content, int array_size);
};


#endif //SKILLED_EAGLE_KEPPADCONTORLLER_HPP





