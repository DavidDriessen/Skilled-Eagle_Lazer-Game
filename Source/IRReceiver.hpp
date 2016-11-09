//
// Created by david on 10/5/2016.
//

#ifndef SKILLED_EAGLE_IR_SENSOREN_HPP
#define SKILLED_EAGLE_IR_SENSOREN_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "DisplayController.hpp"
#include "GameController.hpp"

#define RESOLUTION 200 //1200
#define MAXPULSE 17800 / RESOLUTION
#define MINPULSE 400 / RESOLUTION
#ifndef IRdebuglevel
#define IRdebuglevel 0
#endif

class IRReceiver : public rtos::task<> {
    int pulses[100][2];
    int currentpulse = 0;
    int highpulse, lowpulse;
    hwlib::pin_in &ir;
    rtos::timer interval;

    GameController & game;

#if debug > 0
    void printpulses();
#endif

    void main();

public:
    IRReceiver(hwlib::pin_in &tsop_signal, unsigned int priority, const char *name, GameController & game) :
            task(priority, name),
            ir(tsop_signal),
            interval(this, "IRReceiver_interval"),
            game(game) {};


    void decode_spelleider( char a , char b);
    char check_time_bit(const char stream);
    char * decode_stream(unsigned char streamA, unsigned char streamB);
    void start_decoding_data(void);
};


#endif //SKILLED_EAGLE_IR_SENSOREN_HPP
