//
// Created by Muxbee on 07-11-16.
//

#include "GameController.hpp"

void GameController::main() {
    wait(game_flag);

}

void GameController::shot(int score) {

}

void GameController::enable() {
    game_flag.set();
}

void GameController::disable() {
    game_flag.clear();
}

Gamemode GameController::getGamemode(){
    return gamemode;
}

Weapon GameController::getWeapon() {
    return weapon;
}

