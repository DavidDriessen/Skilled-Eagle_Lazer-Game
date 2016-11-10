//
// Created by david on 10/5/2016.
//

#include "IRSender.hpp"
// no main needed ir sender is passief en werkt op aanvraag van game controller dmv van irsender::fire()

/*
void IRSender::main() {


    for (int h = 0; h < 8; h++) {
        if ((streamA << h) & 0x80)
            send[h] = 1;
        else {
            send[h] = 0;
        }
    }

    for (int h = 8; h < 16; h++) {
        if ((streamB << (h - 8)) & 0x80)
            send[h] = 1;
        else {
            send[h] = 0;
        }
    }

#if IRdebuglevel > 0
    for (int j = 0; j < 16; ++j) {
        hwlib::cout << send[j];
    }
#endif

    while (1) {
        for (int i = 0; i < 16; i++) {
            if (send[i]) {
                ir.set(1);
                interval.set(1600);
                wait(interval);
                ir.set(0);
                interval.set(800);
                wait(interval);
            }
            else {

                ir.set(1);
                interval.set(800);
                wait(interval);

                ir.set(0);
                interval.set(1600);
                wait(interval);
            }
            hwlib::wait_ms(3);
        }
    }
}

*/





void IRSender::main() {
    while (1) {
        rtos::event evt = wait(Send_ir);
        if (evt == Send_ir) {

            encode_stream(speler.read(), data.read(), control.read());

            for (int h = 0; h < 8; h++) {
                if ((streamA << h) & 0x80){
                    send[h] = 1;
                }
                else {
                    send[h] = 0;
                }
            }

            for (int h = 8; h < 16; h++) {
                if ((streamB << (h - 8)) & 0x80) {
                    send[h] = 1;
                }
                else {
                    send[h] = 0;
                }
            }
            //send twice
            for (int z = 0; z < 2; z++) {
                for (int i = 0; i < 16; i++) {
                    if (send[i]) {
                        ir.set(1);
                        interval.set(1600);
                        wait(interval);
                        ir.set(0);
                        interval.set(800);
                        wait(interval);
                    }
                    else {

                        ir.set(1);
                        interval.set(800);
                        wait(interval);

                        ir.set(0);
                        interval.set(1600);
                        wait(interval);
                    }
                }
                hwlib::wait_ms(3);
            }
        }
    }
}

void IRSender::fire() {
    Send_ir.set();
}

void IRSender::send_player_and_weapon(unsigned char player, unsigned char weapon){
    unsigned char Phold = player;
    Phold = Phold | 0x10;
    speler.write(0);
    data.write(Phold);
    control.write(weapon);
};




void IRSender::write_speler( unsigned char speler_data){
    speler.write(speler_data);
}

void IRSender::write_data( unsigned char data_data){
    data.write(data_data);
}

void IRSender::write_control( unsigned char control_data){
    control.write(control_data);
}

void IRSender::encode_stream(char speler, char data, char control){

        //unsigned char streamA = 0;
        //unsigned char streamB = 0;
        //char list[2];
        streamA = (unsigned char) (streamA | 0x01);
        streamA = streamA << 1;

        print_encoded_stream(streamA,streamB);



        for(int y = 0; y < 5; y++){
            if((speler << y) & 0x10 ){
                streamA = (unsigned char) (streamA | 0x01);
                streamA = streamA << 1;
            }
            else{
                streamA = streamA << 1;
            }
        }

        print_encoded_stream(streamA,streamB);

        for(int y = 0; y < 5; y++){
            if(y > 1){

                if((data << y) & 0x10 ){
                    streamB = (unsigned char) (streamB | 0x01);
                    streamB = streamB << 1;
                }
                else{
                    streamB = streamB << 1;
                }

            }

            else{

                if(((data << y) & 0x10) && y == 1 ){
                    streamA = (unsigned char) (streamA | 0x01);
                }
                else if( (data << y) & 0x10 ){
                    streamA = (unsigned char) (streamA | 0x01);
                    streamA = streamA << 1;
                }
                else{
                    if(y == 1){
                        //printf("data_end byteA  A0\n");
                    }
                    else{
                        streamA = streamA << 1;
                        //printf("data A0\n");
                    }

                }
            }
        }

        print_encoded_stream(streamA,streamB);

        for(int y = 0; y < 5; y++){
            if(((control << y) & 0x10) && y == 4 ){
                streamB = (unsigned char) (streamB | 0x01);
            }
            else if((control << y) & 0x10 ){
                streamB = (unsigned char) (streamB | 0x01);
                streamB = streamB << 1;
            }
            else{
                if(y == 4){
                    //printf("control_end byteB B0\n");
                }
                else{
                    streamB = streamB << 1;;

                }

            }
        }

        print_encoded_stream(streamA,streamB);;

    }


void IRSender::print_binary(char print, int lenght){
    for(int h = 0; h < lenght; h++){
        if(( print << h ) & 0x80){
            //std::cout<< "1";
            hwlib::cout<< "1";
        }
        else{
            hwlib::cout<< "0";
            //printf("0");
        }
    }
    //printf("\n");
}

void IRSender::print_encoded_stream(char a, char b){
    print_binary(a,8);
    print_binary(b,8);
    hwlib::cout<< "\n\n";
}