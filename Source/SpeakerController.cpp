//
// Created by MuscioCraft on 8-11-2016.
//

#include "SpeakerController.hpp"
//! The main
/**
 * The main has the sound and it's player in it.
 * It has a wait that waits on the shoot and hit flag.
 * */
void SpeakerController::main() {

    while(1) {

        rtos::event evt = wait(ShootFlag + HitFlag);

        if (evt == ShootFlag) {
            for (int i = 0; i < 200; i++) {
                lsp.set(1);
                SpeakerTimer.set(hwlib::random_in_range(500, 1000) * rtos::us);
                wait(SpeakerTimer);
                lsp.set(0);
                SpeakerTimer.set(hwlib::random_in_range(500, 1000) * rtos::us);
                wait(SpeakerTimer);
            }
        }

        if (evt == HitFlag) {
            for (int k = 0; k < 3; k++) {
                for (int i = 0; i < 200; i++) {
                    lsp.set(1);
                    SpeakerTimer.set(hwlib::random_in_range(500, 600) * rtos::us);
                    wait(SpeakerTimer);
                    lsp.set(0);
                    SpeakerTimer.set(hwlib::random_in_range(500, 600) * rtos::us);
                    wait(SpeakerTimer);
                }
                SpeakerTimer.set(200 * rtos::ms);
                wait(SpeakerTimer);
            }
        }
    }
}

//! Set's the shoot flag to play the shoot sound.
void SpeakerController::shoot(){
    ShootFlag.set();
}
//! Set's the hit flag to play the hit sound.
void SpeakerController::hit(){
    HitFlag.set();
}
