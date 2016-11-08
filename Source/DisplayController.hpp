//
// Created by david on 10/28/2016.
//

#ifndef SKILLED_EAGLE_DISPLAYCONTROLLER_H
#define SKILLED_EAGLE_DISPLAYCONTROLLER_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Weapons.hpp"

class DisplayController : public rtos::task<> {
    rtos::timer interval;
    int time = 0;
    int bullets = 0;
    int weapon = 0;
    int playerid = 0;

    rtos::pool<int> time_pool;
    rtos::pool<int> bullets_pool;
    rtos::pool<int> weapon_pool;
    rtos::pool<int> playerid_pool;
    rtos::flag update;

    void main();

public:
    DisplayController(unsigned int priority, const char *name) :
            task(priority, name),
            interval(this, "DisplayController_interval"),
            time_pool("Display_time_pool"),
            bullets_pool("Display_bullets_pool"),
            weapon_pool("Display_weapon_pool"),
            playerid_pool("Display_playerid_pool"),
            update(this, "Display_update") {};

    void setTime(int time);
    void setBullets(int number);
    void setWeapon(Weapons weapon);
    void setPlayerId(int player);

};

#endif //SKILLED_EAGLE_DISPLAYCONTROLLER_H
