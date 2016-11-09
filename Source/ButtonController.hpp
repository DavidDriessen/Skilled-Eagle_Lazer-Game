//
// Created by david on 11/9/2016.
//

#ifndef SKILLED_EAGLE_BUTTONCONTROLLER_HPP
#define SKILLED_EAGLE_BUTTONCONTROLLER_HPP


#include "GameController.hpp"

class ButtonController : public rtos::task<> {
    GameController &game;
    hwlib::pin_in &btn;

    void main();

public:
    ButtonController(unsigned int priority, const char *name, GameController &game, hwlib::pin_in &btn);

};


#endif //SKILLED_EAGLE_BUTTONCONTROLLER_HPP
