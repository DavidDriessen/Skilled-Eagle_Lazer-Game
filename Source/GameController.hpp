//
// Created by Muxbee on 07-11-16.
//

#ifndef SKILLED_EAGLE_GAMECONTROLLER_HPP
#define SKILLED_EAGLE_GAMECONTROLLER_HPP


#include "hwlib.hpp"
#include "rtos.hpp"
#include "Weapons.hpp"
#include "RegisterController.hpp"

class GameController : public RegisterController, public rtos::task<>{
    private:
        void main();
        int & score;
        Weapons weapon;
        Gamemodes gamemode;
        rtos::flag game_flag;
    public:
        GameController(unsigned int priority,
                       const char *name,
                       int & score,
                       Weapons weapon,
                       Gamemodes gamemode
        ):
                task(priority, name), score(score), weapon(weapon), gamemode(gamemode), game_flag(this, "game_flag"){};
        Weapons getWeapon();
        Gamemodes getGamemode();
        void shot(int score);
        void disable();
        void enable();
};


#endif //SKILLED_EAGLE_GAMECONTROLLER_HPP
