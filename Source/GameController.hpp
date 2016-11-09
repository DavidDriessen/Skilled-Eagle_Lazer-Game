//
// Created by Muxbee on 07-11-16.
//

#ifndef SKILLED_EAGLE_GAMECONTROLLER_HPP
#define SKILLED_EAGLE_GAMECONTROLLER_HPP

class GameTimeController;

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Weapons.hpp"
#include "Gamemodes.hpp"
#include "GameTimeController.hpp"
#include "SpeakerController.hpp"
#include "DisplayController.hpp"
#include "IRSender.hpp"

class GameController : public rtos::task<>{
    private:
        void main();
        GameTimeController & timer;
        SpeakerController & speaker;
        DisplayController & display;
        IRSender & irSender;
        Weapons weapon;
        Gamemodes gamemode;
        int playerId;
        int score[31];
        unsigned int gameTime;
        rtos::flag game_start;
        rtos::flag game_stop;
        rtos::flag shot_flag;
        rtos::flag button_pressed;
        rtos::flag button_released;
        rtos::timer shot_timer;
        rtos::timer sound;
    public:
        GameController(GameTimeController & timer,
                       SpeakerController & speaker,
                       DisplayController & display,
                       IRSender & irSender,
                       unsigned int priority,
                       const char *name
                       ):
                task(priority, name),
                timer(timer),
                speaker(speaker),
                display(display),
                irSender(irSender),
                game_start(this, "game_start"),
                game_stop(this, "game_stop"),
                shot_flag(this, "shot"),
                button_pressed(this, "button_pressed"),
                button_released(this, "button_released"),
                shot_timer(this, "shot_timer"),
                sound(this, "sound")
        {};
        void shot(int playerId, int weaponPower);
        void disable();
        void enable();
        Gamemodes getGamemode();
        Weapons getWeapon();
        void setWeapon(Weapons weapon);
        void setGamemode(Gamemodes gamemode);
        void setPlayerId(int playerId);
};


#endif //SKILLED_EAGLE_GAMECONTROLLER_HPP
