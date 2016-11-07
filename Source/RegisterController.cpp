//
// Created by Muxbee on 07-11-16.
//

#include "RegisterController.hpp"

void RegisterController::startGame(unsigned long time) {
    timer.start(time);
}

void RegisterController::stopGame() {
    timer.stop();
}
