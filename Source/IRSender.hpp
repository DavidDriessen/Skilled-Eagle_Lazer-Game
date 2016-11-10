//
// Created by david on 10/5/2016.
//

#ifndef SKILLED_EAGLE_IR_ZENDER_HPP
#define SKILLED_EAGLE_IR_ZENDER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Weapons.hpp"

#ifndef IRdebuglevel
#define IRdebuglevel 0
#endif

class IRSender : public rtos::task<> {
    hwlib::pin_out &ir;
    rtos::timer interval;
    rtos::flag Send_ir;
    ///
    /// streamA and StreamB are used to hold the 2 bytes to be send by the IRsender.
    /// they are set by calling ecode_stream(char, char, char).
    ///
    unsigned char streamA;
    unsigned char streamB;
    ///
    ///an array for holding the individual bits of streamA and streamB.
    ///
    bool send[16];
    ///
    ///pool to hold the speler.
    ///
    rtos::pool< unsigned char > speler;
    ///
    ///pool to hold the data.
    ///
    rtos::pool< unsigned char > data;
    ///
    ///pool to hold the control.
    ///
    rtos::pool< unsigned char > control;
    ///
    ///main function used by rtos.
    ///

    void main();

public:
    ///
    /// constructor.
    ///
    IRSender(hwlib::pin_out &ir, unsigned int priority, const char *name) :
            task(priority, name),
            ir(ir),
            interval(this, "IRSender_interval"),
            Send_ir(this, "Send_ir"),
            streamA(0),
            streamB(0),
            speler( "speler_pool" ),
            data( "data_pool" ),
            control( "control_pool" ){
                    speler.write(0);
                    data.write(0);
                    control.write(0);
             };


    ///
    /// \param speler
    ///this function writes speler in to the speler pool.
    void write_speler( unsigned char speler);
    ///
    /// \param data
    ///this function writes data in to the data pool.
    void write_data(unsigned char data);
    ///
    /// \param control
    /// this function writes control in to the control pool.
    void write_control(unsigned char control);
    ///
    ///this function is used by the game master to set the playerID of a player and the weapon of the player
    /// \param player
    void send_player_and_weapon(unsigned char player, unsigned char weapon);
    ///
    /// this function is used to fire a shot by setting the send_ir flag.
    ///
    void fire();

    ///
    ///  this function is used to encode speler data and control into 2 bytes.
    ///
    void encode_stream(char speler , char data, char control);
    ///
    /// this function is used to print the 2 bytes containing the ir stream in binary format.
    ///
    void print_encoded_stream(char a, char b);
    ///
    /// this function is used by print_encoded_stream to print.
    /// it prints a single byte in binary format.
    ///
    void print_binary(char print, int lenght);
};


#endif //SKILLED_EAGLE_IR_ZENDER_HPP
