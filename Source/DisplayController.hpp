//
// Created by david on 10/28/2016.
//

#ifndef SKILLED_EAGLE_DISPLAYCONTROLLER_H
#define SKILLED_EAGLE_DISPLAYCONTROLLER_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Weapons.hpp"


class DisplayController : public rtos::task<> {
    hwlib::glcd_oled_buffered &display;

    bool hitBool = false;

    rtos::pool<int> time_pool;
    rtos::pool<int> bullets_pool;
    rtos::pool<int> weapon_pool;
    rtos::pool<int> playerid_pool;
    rtos::pool<int> command_pool;
    rtos::pool<int> master_pool;
    rtos::flag update;

    void main();

    void mainMaster();

public:
    DisplayController(unsigned int priority, const char *name, hwlib::glcd_oled_buffered &display);

    void test();

    void setTime(int time_in_minutes);

    void setBullets(int number_of_bullets);

    void setWeapon(Weapons weapon);

    void setPlayerId(int player_ID);

    void hit();

    void hitClear();

    void masterMenu();

    void playerEdit(int id);

    void commandEdit(int commandInput);

    void weaponEdit(int weapon_ID);


    void confirm();

    void end();
};

#endif //SKILLED_EAGLE_DISPLAYCONTROLLER_H
