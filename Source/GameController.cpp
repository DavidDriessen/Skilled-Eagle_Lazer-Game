//
// Created by Muxbee on 07-11-16.
//

#include "GameController.hpp"
//! Game controller
/**
 * States that the GameController has.
 */
enum State{
    shoot,
    waiting,
    disabled,
    shot,
    reloading
};
/**
 * Main function containing the 5 states in which the player can be.
 *
 * When GameController is started the first state is disabled. If the flag game_start is set the state switches to waiting and it writes data to
 * the pools containing playerId and weapon in IRSender.
 *
 * When state is waiting the game can be stopped with flag game_stop, a hit can be registered with flag shot_flag or a shot can be fired with flag
 * button_pressed. If shot_flag is set the controller will tell the display and speaker to display that the player is hit and play a sound and change the
 * state to shot. If button_pressed is set the state changes to shoot, then checks the bullet count. If there are bullets available to shoot it
 * will tell the IRSender to fire, speaker to play a sound, display to refresh the bullet count, decrease the bullet count and set the fire_timer
 * so the player cant continuously fire. If no bullets are available the state changes to reloading en the timer reload_timer is started.
 *
 * When state is shot the game can be stopped with flag game_stop or the player can "come back alive" when the shot_timer is finished. When shot
 * timer is finished the state changes to waiting and the display is updated to clear the hit message.
 *
 * When state is shoot the game can be stopped with flag game_stop, a hit can be registered with flag shot_flag, the button_released flag can be
 * set to indicate that the fire button is released or another shot can be fired when fire_timer is finished. If no bullets available it changes to
 * state reloading.
 *
 * When state is reloading the game can be stopped with flag game_stop, a hit can registerd with flag shot_flag or the state can change back to
 * waiting when reload_timer is finished. When this happens the player is also given 15 bullets.
 *
 */
void GameController::main() {
    State currentState = waiting;
    while(1) {
        rtos::event evt = wait(game_start + game_stop + button_released + button_pressed + shot_flag + shot_timer + reload_timer + fire_timer);
        switch (currentState){
            case disabled:
                if(evt == game_start) {
                    currentState = waiting;
                    irSender.write_speler((unsigned char) playerId);
                    irSender.write_data((unsigned char) weapon);
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
                        irSender.fire();
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
                        irSender.fire();
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
/**
 * Function called if player is hit. Adds score in array according to weaponPower.
 * @param playerId the ID of the player hitting you.
 * @param weaponPower the amount of points added to your score.
 */
void GameController::shot(int playerId, int weaponPower) {
    shot_flag.set();
    shot_timer.set(10 * rtos::s);
    score[playerId - 1] = weaponPower;
}
/**
 * Function called to start the game and change state to waiting and start the game time.
 */
void GameController::enable() {
    game_start.set();
    timer.start(gameTime);
}
/**
 * Function called to stop the game and change state to disabled.
 */
void GameController::disable() {
    game_stop.set();
}
/**
 * Sets flag to change state when button is pressed.
 */
void GameController::buttonPressed(){
    button_pressed.set();
}
/**
 * Sets flag to change state when button released.
 */
void GameController::buttonReleased(){
    button_released.set();
}
/**
 * returns current gamemode.
 * @return gamemode is the current gamemode.
 */
Gamemodes GameController::getGamemode(){
    return gamemode;
}
/**
 * returns current weapon used.
 * @return weapon is the current weapon.
 */
Weapons GameController::getWeapon() {
    return weapon;
}
/**
 * Sets the current weapon in this class.
 * @param weapon is an Enum from the class Weapons.
 */
void GameController::setWeapon(Weapons weapon){
    this->weapon = weapon;

}
/**
 * Sets the current gamemode in this class.
 * @param gamemode is an Enum from the class Gamemode.
 */
void GameController::setGamemode(Gamemodes gamemode) {
    this->gamemode = gamemode;
}
/**
 * Sets the current player ID in this class.
 * @param playerId is an int used to identify the player.
 */
void GameController::setPlayerId(int playerId){
    this->playerId = playerId;
}

void GameController::setTime(int time) {
    gameTime = time;
}

