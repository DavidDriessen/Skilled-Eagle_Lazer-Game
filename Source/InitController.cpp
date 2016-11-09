//
// Created by MuscioCraft on 7-11-2016.
//

#include "InitController.hpp"

void InitController::PlayerGetter(int player){
    data[0] = player;
}

void InitController::WeaponGetter(int weapon){
    data[1] = weapon;
}

void InitController::CommandGetter(int command){
    data[2] = command;
    hwlib::cout << data[0] << data[1] << data[2];
}