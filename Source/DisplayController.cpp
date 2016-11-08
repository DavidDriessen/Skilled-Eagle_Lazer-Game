//
// Created by david on 10/28/2016.
//

#include "DisplayController.hpp"

void DisplayController::main() {
    while (1) {
        
        interval.set(60 * rtos::s);
        wait(interval);
    }
}

void DisplayController::setTime(int time) {
    time_pool.write(time);
    update.set();
}

void DisplayController::setBullets(int number) {
    bullets_pool.write(number);
    update.set();
}

void DisplayController::setWeapon(Weapons weapon) {
    weapon_pool.write((int) weapon);
    update.set();
}

void DisplayController::setPlayerId(int player) {
    playerid_pool.write(player);
    update.set();
}

