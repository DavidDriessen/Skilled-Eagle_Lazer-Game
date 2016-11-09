//
// Created by david on 11/9/2016.
//

#include "ButtonController.hpp"

void ButtonController::main() {
    int state = 0;
    while (1) {
        if (btn.get() == 1 && state == 1) {
            game.buttonPressed();
            state = 0;
        } else if (btn.get() == 0 && state == 0) {
            game.buttonReleased();
            state = 1;
        }
        interval.set(100 * rtos::ms);
        wait(interval);
    }
}
