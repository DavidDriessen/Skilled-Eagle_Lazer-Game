//
// Created by MuscioCraft on 7-11-2016.
//

#ifndef SKILLED_EAGLE_WEAPONS_HPP
#define SKILLED_EAGLE_WEAPONS_HPP


enum class Weapons{
    AK47 = 1,
    M9 = 2,
    MP5 = 3,
    UZI = 4,
    RPG = 5,
    IPOD = 6,
    TIMMY = 7,
    PARKER = 8,
    JIMMY = 9


};
char* weapon_names[] = {(char *) "AK47", (char *) "M9", (char *) "MP5", (char *) "UZI", (char *) "RPG", (char *) "IPOD",
                        (char *) "TIMMY", (char *) "PARKER", (char *) "JIMMY"};

char* GetWeaponName(int name, int size = sizeof(weapon_names)/sizeof(weapon_names[0]))
{

    if(name > size)
    {
        return (char *) "Unknow";
    }
    return weapon_names[name-1];
}


#endif //SKILLED_EAGLE_WEAPONS_HPP
