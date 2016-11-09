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
#include "SpeakerController.hpp"
#include "DisplayController.hpp"

using namespace hwlib;

class KeyPadController: public rtos::task<>{
private:
    DisplayController & display;
    InitController & init;
    hwlib::istream & keypad;
    rtos::timer KeyTimer;
    SpeakerController & speak;


    void main();

public:
    KeyPadController(unsigned int priority, const char *name, InitController &init, hwlib::istream &pad,
                         SpeakerController &speak, DisplayController &display) :
            task(priority, name), init(init), keypad(pad), KeyTimer(this, "KeyPadTimer"), speak(speak),
            display(display) {};

    int array_to_intger(int *content, int array_size);
};


#endif //SKILLED_EAGLE_KEPPADCONTORLLER_HPP





