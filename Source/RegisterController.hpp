//
// Created by Muxbee on 07-11-16.
//

#ifndef SKILLED_EAGLE_REGISTERCONTROLLER_HPP
#define SKILLED_EAGLE_REGISTERCONTROLLER_HPP


#include "hwlib.hpp"
#include "rtos.hpp"
#include "GameTimeController.hpp"
#include "Weapons.hpp"

 class RegisterController{
    private:
        GameTimeController & timer;

    public:
        RegisterController(GameTimeController & timer) : timer(timer){};

        void startGame(unsigned long time);

        void stopGame();

        virtual void setWeapon(Weapons) = 0;

        virtual void setGamemode(Gamemodes) = 0;
};


#endif //SKILLED_EAGLE_REGISTERCONTROLLER_HPP
