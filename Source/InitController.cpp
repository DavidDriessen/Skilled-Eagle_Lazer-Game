//
// Created by MuscioCraft on 7-11-2016.
//

#include "InitController.hpp"

//! Gets and sends Player ID
void InitController::PlayerGetter(int player){
    data[0] = (char)player;
    send.write_speler(data[0]);
}

//! Gets and sends Weapon ID
void InitController::WeaponGetter(int weapon){
    data[1] = (char)weapon;
    send.write_data(data[1]);
}

//! Gets and sends Command ID
void InitController::CommandGetter(int command){
    data[2] = (char)command;
    send.write_command(data[2]);


}