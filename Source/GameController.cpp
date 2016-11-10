//
// Created by Muxbee on 07-11-16.
//

#include "GameController.hpp"
enum State{
    shoot,
    waiting,
    disabled,
    shot,
    reloading
};

void GameController::main() {
    State currentState = waiting;
    while(1) {
        rtos::event evt = wait(game_start + game_stop + button_released + button_pressed + shot_flag + shot_timer + reload_timer + fire_timer);
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
                    speaker.hit();
                }
                if(evt == button_pressed){
                    currentState = shoot;
                    if(bullets != 0){
                        bullets --;
                        irSender.fire(playerId, weapon);
                        speaker.shoot();
                        display.setBullets(bullets);
                        fire_timer.set(1 * rtos::s);
                    }
                    if(bullets == 0){
                        currentState = reloading;
                        reload_timer.set(5 * rtos::s);
                    }

                }
                break;
            case State::shot:
                if(evt == game_stop){
                    currentState = disabled;
                }
                if(evt == shot_timer){
                    currentState = waiting;
                    display.hitClear();
                }
                break;
            case shoot:
                if(evt == shot_flag)
                {
                    currentState = State::shot;
                    display.hit();
                    speaker.hit();
                }
                if(evt == button_released){
                    currentState = waiting;
                }
                if(evt == game_stop){
                    currentState = disabled;
                }
                if(evt == fire_timer){
                    if(bullets != 0){
                        bullets --;
                        irSender.fire(playerId, weapon);
                        speaker.shoot();
                        display.setBullets(bullets);
                        fire_timer.set(1 * rtos::s);
                    }
                    if(bullets == 0){
                        currentState = reloading;
                        reload_timer.set(5 * rtos::s);
                    }
                }
                break;

            case reloading:
                if(evt == shot_flag)
                {
                    currentState = State::shot;
                    display.hit();
                    speaker.hit();
                }
                if(evt == game_stop)
                {
                    currentState = disabled;
                }
                if(evt == reload_timer)
                {
                    currentState = waiting;
                    bullets = 15;
                    display.setBullets(bullets);
                }
        }
    }
}

void GameController::shot(int playerId, int weaponPower) {
    shot_flag.set();
    shot_timer.set(10 * rtos::s);
    score[playerId - 1] = weaponPower;
}

void GameController::enable() {
    game_start.set();
    timer.start(gameTime);
}

void GameController::disable() {
    game_stop.set();
}

void GameController::buttonPressed(){
    button_pressed.set();
}

void GameController::buttonReleased(){
    button_released.set();
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

void GameController::setPlayerId(int playerId){
    this->playerId = playerId;
}

