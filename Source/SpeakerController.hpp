//
// Created by MuscioCraft on 8-11-2016.
//

#ifndef SKILLED_EAGLE_SPEAKERCONTROLLER_HPP
#define SKILLED_EAGLE_SPEAKERCONTROLLER_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "bmptk.h"

class SpeakerController : public rtos::task<>{
private:
    hwlib::pin_out & lsp;
    void await( long long int t );
    void beep(int f, int d, int fd);
    rtos::timer SpeakerTimer;
    rtos::flag ShootFlag;
    rtos::flag HitFlag;
    void main();
public:
    SpeakerController(hwlib::pin_out & lsp):
    lsp(lsp), SpeakerTimer(this, "SpeakerTimer"), ShootFlag(this, "ShootFlag"), HitFlag(this ,"HitFlag") {};


    void shoot();
    void hit();


};



#endif //SKILLED_EAGLE_SPEAKERCONTROLLER_HPP


