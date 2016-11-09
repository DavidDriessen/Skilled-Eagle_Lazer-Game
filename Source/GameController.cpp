//
// Created by Muxbee on 07-11-16.
//

#include "GameController.hpp"

void GameController::main() {
    wait(game_start);
    timer.start(gameTime);
    //luisteren naar schieten

}

void GameController::shot(int &score) {

}

void GameController::enable() {
    game_start.set();
}

void GameController::disable() {
    game_stop.set();
}

Gamemodes GameController::getGamemode(){
    return gamemode;
}

Weapons GameController::getWeapon() {
    return weapon;
}

void GameController::setWeapon(Weapons weapon){

}

void GameController::setGamemode(Gamemodes gamemode) {}

