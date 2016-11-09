//
// Created by MuscioCraft on 7-11-2016.
//

#ifndef SKILLED_EAGLE_INITCONTROLLER_HPP
#define SKILLED_EAGLE_INITCONTROLLER_HPP

#include "Weapons.hpp"
#include "hwlib.hpp"

class InitController{
private:
    int player  = 0;
    int weapon  = 0;
    int command = 0;
    int data[3];
public:

    void PlayerGetter(int player);
    void WeaponGetter(int weapon);
    void CommandGetter(int command);


};


#endif //SKILLED_EAGLE_INITCONTROLLER_HPP
