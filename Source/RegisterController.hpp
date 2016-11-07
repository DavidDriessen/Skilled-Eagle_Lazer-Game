//
// Created by Muxbee on 07-11-16.
//

#ifndef SKILLED_EAGLE_REGISTERCONTROLLER_HPP
#define SKILLED_EAGLE_REGISTERCONTROLLER_HPP


#include "hwlib.hpp"
#include "rtos.hpp"
#include "enums.hpp"
#include "GameTimeController.hpp"

 class RegisterController{
    private:
        GameTimeController & timer;

    public:
        RegisterController(GameTimeController & timer) : timer(timer){};

        void startGame(unsigned long time);

        void stopGame();

        virtual void setWeapon(Weapon) = 0;

        virtual void setGamemode(Gamemode) = 0;
};


#endif //SKILLED_EAGLE_REGISTERCONTROLLER_HPP
