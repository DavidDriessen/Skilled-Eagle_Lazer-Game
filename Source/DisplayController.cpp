//
// Created by david on 10/28/2016.
//

#include "DisplayController.hpp"

void DisplayController::main() {
    while (1) {
        hwlib::cout << data.read() << '\n';
        interval.set(10 * rtos::ms);
        wait(interval);
    }
}

void DisplayController::test(char *c) {
    data.write(c);
}

void DisplayController::ir(int **pulses, int currentpulse, int RESOLUTION) {
    for (int i = 0; i < currentpulse; i++) {
        if (pulses[i][1] > 5) {
            hwlib::cout << "1";
        } else {
            hwlib::cout << "0";
        }
    }
    hwlib::cout << "\n";
}
