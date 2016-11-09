//
// Created by david on 11/9/2016.
//

#include "ButtonController.hpp"

ButtonController::ButtonController(unsigned int priority, const char *name, GameController &game, hwlib::pin_in &btn) :
        task(priority, name),
        game(game),
        btn(btn) {}

void ButtonController::main() {

}
