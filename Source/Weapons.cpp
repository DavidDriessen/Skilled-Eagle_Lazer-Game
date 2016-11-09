//
// Created by MuscioCraft on 9-11-2016.
//

#include "Weapons.hpp"

char* weapon_names[] = {(char *) "AK47", (char *) "M9", (char *) "MP5", (char *) "UZI", (char *) "RPG", (char *) "IPOD",
                        (char *) "TIMMY", (char *) "PARKER", (char *) "JIMMY"};

char* GetWeaponName(int name)
{
    int size = sizeof(weapon_names)/sizeof(weapon_names[0]);
    if(name > size)
    {
        return (char *) "Unknow";
    }
    return weapon_names[name-1];
}