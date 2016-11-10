//
// Created by david on 10/5/2016.
//

#ifndef SKILLED_EAGLE_IR_SENSOREN_HPP
#define SKILLED_EAGLE_IR_SENSOREN_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "DisplayController.hpp"
#include "GameController.hpp"

#define RESOLUTION 100 //1200
#define MAXPULSE 17800 / RESOLUTION
#define MINPULSE 400 / RESOLUTION
#ifndef IRdebuglevel
#define IRdebuglevel 0
#endif

class IRReceiver : public rtos::task<> {
    ///
    ///speler, data and control variables.
    ///
    unsigned char speler;
    unsigned char data;
    unsigned char control;
    ///
    ///variabels used to read the irpulses.
    ///
    int pulses[100][2];
    int currentpulse = 0;
    int highpulse, lowpulse;
    hwlib::pin_in &ir;


    rtos::timer interval;
    ///
    ///gamecontroller.
    ///
    GameController & game;

//#if IRdebuglevel > 0
    void printpulses();
//#endif
    ///
    ///main function used by rtos.
    ///
    void main();

public:
    ///
    ///constructor
    ///
    IRReceiver(hwlib::pin_in &tsop_signal, unsigned int priority, const char *name, GameController & game) :
            task(priority, name),
            ir(tsop_signal),
            interval(this, "IRReceiver_interval"),
            game(game) {};

    ///
    ///this function is used to differentiate between the game master and normal player.
    ///
    void write_detected_ir(unsigned char a , unsigned char b, unsigned char c);
    ///
    /// this function is used to check if bit 5 of data is set.
    /// if this bit is set and player is 0 it states as an extra command.
    /// if this bit is 0 it means that data hold the game time.
    /// \return
    char check_time_bit(const char stream);
    ///
    /// this function takes 2 bytes as char's which hold the received 16 bit IRstream.
    /// these 2 bytes are then decoded to 3 chars ( speler , data and , control.
    ///
    void decode_stream(unsigned char streamA, unsigned char streamB);
    ///
    ///this function takes the printpulses array created by main
    ///and creates 2 bytes which hold the values contained in the IR bitStream.
    ///
    void print_binary(char print, int lenght);
    void start_decoding_data(void);

};


#endif //SKILLED_EAGLE_IR_SENSOREN_HPP
