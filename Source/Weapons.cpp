//
// Created by MuscioCraft on 9-11-2016.
//

#include "Weapons.hpp"
//! A array of names
char* weapon_names[] = {(char *) "AK47", (char *) "M9", (char *) "MP5", (char *) "UZI", (char *) "RPG", (char *) "IPOD",
                        (char *) "TIMMY", (char *) "PARKER", (char *) "JIMMY"};
//! A name gettter
/*! This function graps a element out of weapon_names[] and returns it.*/
char* GetWeaponName(int name)
{
    int size = sizeof(weapon_names)/sizeof(weapon_names[0]); /// Gets array size.
    if(name > size)
    {
        return (char *) "Unknow";                           /// If the selceted element doesn't exists it will return "Unknow".
    }
    return weapon_names[name-1];
}