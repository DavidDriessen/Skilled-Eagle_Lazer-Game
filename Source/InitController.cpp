//
// Created by MuscioCraft on 7-11-2016.
//

#include "InitController.hpp"

void InitController::PlayerGetter(int player){
    data[0] = (char)player;
}

void InitController::WeaponGetter(int weapon){
    data[1] = (char)weapon;
}

void InitController::CommandGetter(int command){
    data[2] = (char)command;
    //IRsender::encode_stream(data[0], data[1], data[2]);
    hwlib::cout << data[0] << data[1] << data[2];
}