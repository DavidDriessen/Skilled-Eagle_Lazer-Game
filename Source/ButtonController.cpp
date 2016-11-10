//
// Created by david on 11/9/2016.
//

#include "ButtonController.hpp"
//!Button Controller
/**
 * Button Controller contains 2 states. It starts in the not shooting state. If the button is pressed button is high and state is not shooting so it calls
 * the game controller function buttonPressed() and state changes to shooting. If button is released and state was shooting the buttonReleased()
 * function of the game controller is called and state changes to not shooting.
 */
void ButtonController::main() {
    int state = 1;
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
