//
// Created by Muxbee on 07-11-16.
//
#include "GameTimeController.hpp"

void GameTimeController::start(unsigned long time){
    gameTime.set(time);
}

void GameTimeController::stop(){
    gameTime.set(0);
    gameController.disable();
}
void GameTimeController::main(){
    for(;;){
        wait(gameTime);
        stop();
    }

}
