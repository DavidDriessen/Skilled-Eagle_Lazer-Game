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

class GameController : public rtos::task<>{
    private:
        void main();
        GameTimeController & timer;
        Weapons weapon;
        Gamemodes gamemode;
        int playerId;
        unsigned int gameTime;
        rtos::flag game_start;
        rtos::flag game_stop;
    public:
        GameController(GameTimeController & timer,
                       unsigned int priority,
                       const char *name
                       ):
                task(priority, name),
                timer(timer),
                game_start(this, "game_start"),
                game_stop(this, "game_stop")
        {};
        void shot(int &score);
        void disable();
        void enable();
        Gamemodes getGamemode();
        Weapons getWeapon();
        void setWeapon(Weapons weapon);
        void setGamemode(Gamemodes gamemode);
};


#endif //SKILLED_EAGLE_GAMECONTROLLER_HPP
