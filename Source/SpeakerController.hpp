//
// Created by MuscioCraft on 8-11-2016.
//

#ifndef SKILLED_EAGLE_SPEAKERCONTROLLER_HPP
#define SKILLED_EAGLE_SPEAKERCONTROLLER_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "bmptk.h"
//! SpeakerController class / rtos task.
/** This class contains all the logic and sounds to play*/

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
    //! The constructor.
    /*!
     * constructor contains the pin where the sound will be send to
     * and it conains rtos task's , flags and a timer.
    */
    SpeakerController(unsigned int priority, const char* name, hwlib::pin_out & lsp):
    task(priority, name),  lsp(lsp), SpeakerTimer(this, "SpeakerTimer"), ShootFlag(this, "ShootFlag"), HitFlag(this ,"HitFlag") {};


    void shoot();
    void hit();


};



#endif //SKILLED_EAGLE_SPEAKERCONTROLLER_HPP


