//
// Created by Muxbee on 07-11-16.
//

#include "GameController.hpp"
enum State{
    shoot,
    waiting,
    disabled,
    shot
};

void GameController::main() {
    State currentState = disabled;
    while(1) {
        rtos::event evt = wait(game_start + game_stop + button_released + button_pressed + shot_flag + shot_timer);
        switch (currentState){
            case disabled:
                if(evt == game_start) {
                    currentState = waiting;
                }
                break;
            case waiting:
                if(evt == game_stop){
                    currentState = disabled;
                }
                if(evt == shot_flag){
                    currentState = State::shot;
                    display.hit();
                    for(int i = 0; i < 3; i++){
                        speaker.click();
                        sound.set(200 * rtos::ms);
                        wait(sound);
                    }

                }
                if(evt == button_pressed){
                    currentState = shoot;
                    irSender.fire(playerId, weapon);
                    speaker.peew();
                }
            case State::shot:
                if(evt == game_stop){
                    currentState = disabled;
                }
                if(evt == shot_timer){
                    currentState = waiting;
                    display.hitClear();
                }
            case shoot:
                if(evt == shot_flag)
                {
                    currentState = State::shot;
                    display.hit();
                    for(int i = 0; i < 3; i++){
                        speaker.click();
                        sound.set(200 * rtos::ms);
                        wait(sound);
                    }
                }
                if(evt == button_released){
                    currentState = waiting;
                }
                if(evt == game_stop){
                    currentState = disabled;
                }
        }
    }
}

void GameController::shot(int &score) {
    shot_flag.set();
    shot_timer.set(10 * rtos::s);

}

void GameController::enable() {
    game_start.set();
    timer.start(gameTime);
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
    this->weapon = weapon;

}

void GameController::setGamemode(Gamemodes gamemode) {
    this->gamemode = gamemode;
}

