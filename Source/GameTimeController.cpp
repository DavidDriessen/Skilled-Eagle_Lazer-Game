//
// Created by Muxbee on 07-11-16.
//
#include "GameTimeController.hpp"
//! Game timer controller
/**
 * Starts the game timer and the timer that updates the display.
 *
 * @param time is an unsigned int indicating the duration of the total game duration.
 */
void GameTimeController::start(unsigned long time){
    this->time = time;
    gameTime.set(time);
    updateTime.set(60 * rtos::s);
    displayController.setTime((int) time);
}
/**
 * Stops the game that is running in the GameController.
 */
void GameTimeController::stop(){
    gameController->disable();
}
/**
 * Main function, waiting for 2 flags. If game time runs out, stop game. if update timer runs out change and update the display.
 */
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
