//
// Created by MuscioCraft on 7-11-2016.
//

#ifndef SKILLED_EAGLE_WEAPONS_HPP
#define SKILLED_EAGLE_WEAPONS_HPP
//! Enum class

/** This class contains enums(Weapon names)*/
enum class Weapons{
    AK47 = 1,     /*!This is the first weapon*/
    M9 = 2,       /*!This is the second weapon*/
    MP5 = 3,      /*!This is the third weapon*/
    UZI = 4,      /*!This is the fourth weapon*/
    RPG = 5,      /*!This is the fifth weapon*/
    IPOD = 6,     /*!This is the sixth weapon*/
    TIMMY = 7,    /*!This is the seventh weapon*/
    PARKER = 8,   /*!This is the eighth weapon*/
    JIMMY = 9     /*!This is the ninth weapon*/

};
    char* GetWeaponName(int name);


#endif //SKILLED_EAGLE_WEAPONS_HPP
