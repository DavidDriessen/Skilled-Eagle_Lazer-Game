//
// Created by MuscioCraft on 8-11-2016.
//

#include "SpeakerController.hpp"
void SpeakerController::main() {

    while(1) {
        //beep( 20000, 200000, 990 );
        rtos::event evt = wait(ShootFlag + HitFlag);

        if (evt == ShootFlag) {
            for (int i = 0; i < 200; i++) {
                lsp.set(1);
                SpeakerTimer.set(hwlib::random_in_range(200, 400) * rtos::us);
                wait(SpeakerTimer);
                lsp.set(0);
                SpeakerTimer.set(hwlib::random_in_range(100, 500) * rtos::us);
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


void SpeakerController::await( long long int t ){
    while( t > hwlib::now_us() ){}
}

/*void SpeakerController::beep(int f, int d, int fd = 1000){
    auto t = hwlib::now_us();
    auto end = t + d;
    while( end > hwlib::now_us() ){
        auto p = 500000 / f;
        f = f * fd / 1000;
        lsp.set( 1 );
        await( t += p );
        lsp.set( 0 );
        await( t += p );
    }
}*/

void SpeakerController::shoot(){
    ShootFlag.set();
}

void SpeakerController::hit(){
    HitFlag.set();
}
