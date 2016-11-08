//
// Created by MuscioCraft on 8-11-2016.
//

#include "SpeakerController.hpp"



void SpeakerController::await( long long int t ){
    while( t > hwlib::now_us() ){}
}

void SpeakerController::beep(int f, int d, int fd = 1000){
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
}

void SpeakerController::peew(){
    beep( 20000, 200000, 990 );
}

void SpeakerController::beep3(){
    for( int i = 0; i < 3; i++ ){
        beep( 1000, 50000 );
        hwlib::wait_us( 20000 );
    }
}

void SpeakerController::ohhh() {
    for (int i=1000; i<2000; i=i*1.02) {
        beep(i,10000);
    }
    for (int i=2000; i>1000; i=i*.98) {
        beep(i,10000);
    }
}


void SpeakerController::uhoh() {
    for (int i=1000; i<1244; i=i*1.01) {
        beep(i,10000);
    }
    hwlib::wait_us( 30000 );
    for (int i=1244; i>1108; i=i*.99) {
        beep(i,10000);
    }
}

void SpeakerController::noise() {
    for (int i = 0; i < 200; i++ ){
        lsp.set( ( hwlib::rand() & 0x01 ) == 0);
        hwlib::wait_us( 1000 );
    }
}

void SpeakerController::noise2(){
    for (int i = 0; i < 200; i++ ){
        lsp.set( 1 );
        hwlib::wait_us( hwlib::random_in_range( 500, 2000 ));
        lsp.set( 0 );
        hwlib::wait_us( hwlib::random_in_range( 500, 2000 ));
    }
}

void SpeakerController::click(){
    for (int i = 0; i < 200; i++ ){
        lsp.set( 1 );
        hwlib::wait_us( hwlib::random_in_range( 500, 600 ));
        lsp.set( 0 );
        hwlib::wait_us( hwlib::random_in_range( 500, 600 ));
    }
}