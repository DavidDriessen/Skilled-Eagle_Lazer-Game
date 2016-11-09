//
// Created by david on 10/5/2016.
//

#include "IRReceiver.hpp"

#if debug > 0
void IRReceiver::printpulses(void) {
#if IRdebuglevel == 2
    hwlib::cout << "\n\r\n\rReceived: \n\rOFF \tON\n";
    for (int i = 0; i < currentpulse; i++) {
        hwlib::cout << pulses[i][0] * RESOLUTION;  //verwissel deze 0 en 1 om positie van high and low te wissellen
        hwlib::cout << " usec, ";
        hwlib::cout << pulses[i][1] * RESOLUTION;
        hwlib::cout << " usec\n";
    }
    while(1){}
#elif IRdebuglevel == 1
    for (int i = 0; i < currentpulse; i++) {
        //if (pulses[i][1] > pulses[i + 1][0]) {
        if (pulses[i][1] * RESOLUTION > 1000) {
            hwlib::cout << "1";
        } else {
            hwlib::cout << "0";
        }
    }
    hwlib::cout << "\n";
#endif
}
#endif

void IRReceiver::main() {
    while (1) {
        currentpulse = 0;
        while (currentpulse < 17) {
            // zet de timing variabelen op 0
            highpulse = lowpulse = 0;
            // terwijl het signaal uit de decoder laag is
            while (ir.get() == 1) {
                // verhoog tijd variabele en wacht aantal us
                highpulse++;
                hwlib::wait_us(RESOLUTION);
//                interval.set(RESOLUTION);
//                wait(interval);
                // als deze pulse langer duurd dan time out en er is 1 pulse gezien
                // print de pulsen en return
                if ((highpulse >= MAXPULSE)) {
                    currentpulse = 0;
                    break;
                }
            }
            if (highpulse <= MINPULSE) {
                currentpulse = 0;
            }
            // sla de pulse op in het pulse array
            pulses[currentpulse][0] = highpulse;
            // terwijl het signaal uit de decoder hoog is
            while (ir.get() == 0) {
                // verhoog tijd variabele en wacht aantal us
                lowpulse++;
                hwlib::wait_us(RESOLUTION);
//                interval.set(RESOLUTION);
//                wait(interval);
                // als deze pulse langer duurd dan time out en er is 1 pulse gezien
                // print de pulsen en return
                if ((lowpulse >= MAXPULSE)) {
                    currentpulse = 0;
                    break;
                }
            }
            if (lowpulse <= MINPULSE) {
                currentpulse = 0;
            }
            // sla de pulse op in het pulse array
            pulses[currentpulse][1] = lowpulse;
            // verhoog positie in pulse array
            currentpulse++;
        }
#if debug > 0
        printpulses();
        hwlib::wait_us(3000);
#endif
        start_decoding_data();
    }
}

void IRReceiver::start_decoding_data(void) {
    unsigned char streamA;
    unsigned char streamB;
/*
    for (int i = 0; i < currentpulse; i++) {
        hwlib::cout << pulses[i][0] * RESOLUTION;  //verwissel deze 0 en 1 om positie van high and low te wissellen
        hwlib::cout << " usec, ";
        hwlib::cout << pulses[i][1] * RESOLUTION;
        hwlib::cout << " usec\n";
    }
*/
    for (int i = 0; i < currentpulse; i++) {
        if(i > 7) {
            if (i == 16) {
                if (pulses[i][1] * RESOLUTION > 1000) {
                    streamB = streamB | 0x01;
                }
                else {
                    //nothing
                }
            }
            else {
                if (pulses[i][1] * RESOLUTION > 1000) {
                    //hwlib::cout << "1\n";
                    streamB = streamB | 0x01;
                    streamB = streamB << 1;
                } else if (pulses[i][1] * RESOLUTION < 1000) {
                    //hwlib::cout << "0\n";
                    streamA = streamA << 1;

                }
            }
        }
         else{
                if(i == 7){
                    if (pulses[i][1] * RESOLUTION  > 1000) {
                        streamA = streamA | 0x01;
                    }
                    else{
                        //nothing
                    }
                }
                else{
                    if (pulses[i][1] * RESOLUTION  > 1000) {
                        //hwlib::cout << "1\n";
                        streamA = streamA | 0x01;
                        streamA = streamA << 1;

                    }
                    else if(pulses[i][1] * RESOLUTION < 1000 ) {
                        //hwlib::cout << "0\n";
                        streamA = streamA << 1;

                    }

                }
            }


    }
}

void IRReceiver::decode_spelleider( char a , char b){
    if(a == 0 && b == 0){
        //printf("\ngame start  send\n");
        //start game commando ontvangen
    }
    else if(a == 0){
        if(check_time_bit(b)){
            //printf("\noverige data\n");
            //overige data ontvangen
        }
        else{
            //printf("\ntime data send %d\n", b);
            //game time commando ontvangen
        }
    }


}

char IRReceiver::check_time_bit(const char stream){
    char hold = stream;
    if(( hold << 3) & 0x80){
        return 1;
    }
    else{
        return 0;

    }

}

void IRReceiver::decode_stream(unsigned char streamA, unsigned char streamB){

    char speler =0;
    char data = 0;
    char control = 0;
    char list[3];


    for(int y = 1; y < 6; y++){
        if(((streamA << y) & 0x80) && y == 5){
            speler = speler | 0x01;
            //printf("speler_end A1\n");
        }
        else if((streamA << y) & 0x80 ){
            speler = speler | 0x01;
            speler = speler << 1;
            //printf("speler A1\n");
        }
        else{
            if(y == 5){
                //printf("speler_end A0\n");
            }
            else{
                speler = speler << 1;
                //printf("speler A0\n");
            }
        }
    }
   // printf("\n%d speler\n\n", speler);

    for(int y = 6; y < 11; y++){
        if(y > 7){
            if(((streamB << (y-8)) & 0x80) && y == 10 ){
                data = data | 0x01;
               // printf("data_end B1\n");
            }
            else if((streamB << (y-8)) & 0x80 ){
                data = data | 0x01;
                data = data << 1;
                //printf("data B1\n");
            }
            else{
                if(y == 10){
                    //printf("data_end B0\n");
                }
                else{
                    data = data << 1;
                    //printf("data B0\n");
                }

            }
        }
        else{
            if((streamA << y) & 0x80 ){
                data = data | 0x01;
                data = data << 1;
                //printf("data A1\n");
            }
            else{
                data = data << 1;
                //printf("data A0\n");
            }
        }
    }

   // printf("\n%d data\n\n", data);


    for(int y = 11; y < 16; y++){
        if(((streamB << (y-8)) & 0x80) && y == 15){
            control = control | 0x01;
            //printf("control_end B1\n");
        }
        else if((streamB << (y-8)) & 0x80 ){
            control = control | 0x01;
            control = control << 1;
            //printf("control B1\n");
        }
        else{
            if(y == 15){
                //printf("control_end B0\n");
            }
            else{
                control = control << 1;
                //printf("control B0\n");
            }
        }
    }

    //printf("\n%d control\n", control);
    list[0] = speler;
    list[1] = data;
    list[2] = control;

    // hier komt iets van channel.write shot data
    hwlib::cout << list[0];

}