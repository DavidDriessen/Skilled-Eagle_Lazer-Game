//
// Created by MuscioCraft on 7-11-2016.
//

#include "InitController.hpp"

//! Gets and sends Player ID
void InitController::PlayerGetter(int player) {
    data[0] = (char) player;
}

//! Gets and sends Weapon ID
void InitController::WeaponGetter(int weapon) {
    data[1] = (char) weapon;
}

//! Gets and sends Command ID
void InitController::CommandGetter(int command) {
    if (command == 1) {
        send.send_player_and_weapon((unsigned char) data[0], (unsigned char) data[1]);
    } else if (command == 2) {
        send.send_start_game();
    } else {
        send.send_gametime(command);
    }


}