//
// Created by Muxbee on 07-11-16.
//
#include "GameTimeController.hpp"

void GameTimeController::start(unsigned long time){
    this->time = time;
    gameTime.set(time);
    updateTime.set(30 * rtos::s);

}

void GameTimeController::stop(){
    gameController->disable();
}
void GameTimeController::main(){
    for(;;){
        rtos::event evt = wait(gameTime + updateTime);
        if(evt == gameTime) {
            stop();
        }
        if(evt == updateTime){
            time --;
            displayController.setTime(time);
        }
    }

}
