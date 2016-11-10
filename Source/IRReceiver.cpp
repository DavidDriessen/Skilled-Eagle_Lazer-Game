//
// Created by david on 10/5/2016.
//

#include "IRReceiver.hpp"

#if IRdebuglevel > 0

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
    // lees de pulses in
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
#if IRdebuglevel > 0
        printpulses();
        hwlib::wait_us(3000);
#endif

        start_decoding_data();


        //wait 10 ms rtos wait

        interval.set(10 * rtos::ms);
        wait(interval);

    }
}

void IRReceiver::start_decoding_data(void) {
    int shift = 0;


    //start het bouwen van de 2 bytes
    if (pulses[0][1] * RESOLUTION <= 1000 && pulses[1][1] * RESOLUTION > 1000) {
        shift = 1;
        //hwlib::cout << "shift bits 1 place\n";
    } else if (pulses[0][1] * RESOLUTION <= 1000 && pulses[1][1] * RESOLUTION <= 1000) {
        //hwlib::cout << "wrong data received\n";
        return;
    } else {
        // hwlib::cout << "error\n";
        return;
    }


    unsigned char streamA = 0;
    unsigned char streamB = 0;


    for (int i = shift; i < 16 + shift; i++) {
        if (i > 7 + shift) {
            if (i == 15 + shift) {
                if (pulses[i][1] * RESOLUTION > 1000) {
                    streamB = streamB | 0x01;
                } else {
                    //nothing
                }
            } else {
                if (pulses[i][1] * RESOLUTION > 1000) {
                    //hwlib::cout << "1\n";
                    streamB = streamB | 0x01;
                    streamB = streamB << 1;
                } else if (pulses[i][1] * RESOLUTION <= 1000) {
                    //hwlib::cout << "0\n";
                    streamB = streamB << 1;

                }
            }
        } else {
            if (i == 7 + shift) {
                if (pulses[i][1] * RESOLUTION > 1000) {
                    streamA = streamA | 0x01;
                } else {
                    //nothing
                }
            } else {
                if (pulses[i][1] * RESOLUTION > 1000) {
                    //hwlib::cout << "1\n";
                    streamA = streamA | 0x01;
                    streamA = streamA << 1;

                } else if (pulses[i][1] * RESOLUTION <= 1000) {
                    //hwlib::cout << "0\n";
                    streamA = streamA << 1;

                }

            }
        }

    }
    //start het decoderen van de 2 bytes

    decode_stream(streamA, streamB);
}


//deze functie moet in gamecontroller om te bepalen welke actie moet worden ondernomen
//want nadat shot_data verstuurt wrdt naar game controller wordt daar nagegaan of het een standaard shot of een commando is






void IRReceiver::write_detected_ir(unsigned char a, unsigned char b, unsigned char c) {

    if (speler > 0) {
        game.shot(a, b);
        //hwlib::cout << "\nnormal player shot received%d\n";
    } else if (a == 0 && b == 0) {
        game.enable();
        // hwlib::cout << "\ngame start command  received\n";
    } else {
        if (a == 0) {
            if (check_time_bit(b)) {
                game.setPlayerId(b - 16);
                game.setWeapon((Weapons) c);
                // hwlib::cout << "\nweappon and player id command  received\n";
            } else {
                game.setTime(b);
                // hwlib::cout << "\ngametime command received " << b + '0' << "\n";
            }
        }
    }

    //hwlib::cout << "\nspeler " << a << "\ndata  " << b << "\ncontrol  " << c << "\n";
}

//deze functie moet in gamecontroller om te bepalen welke actie moet worden ondernomen decode spelleider maakt gebruik van check_time_bit
//want nadat shot_data verstuurt wrdt naar game controller wordt daar nagegaan of het een standaard shot of een commando is

char IRReceiver::check_time_bit(const char stream) {
    if (stream & 0b00010000) {
        return 1;
    } else {
        return 0;

    }

}


void IRReceiver::decode_stream(unsigned char streamA, unsigned char streamB) {
    speler = 0;
    data = 0;
    control = 0;
    //decodeer de 2 bytes
    // hwlib::cout << "binary received \n";
    //print_binary(streamA, 8);
    //print_binary(streamB, 8);
    //hwlib::cout << "\n";


    for (int y = 1; y < 6; y++) {
        if (((streamA << y) & 0x80) && y == 5) {
            speler = speler | 0x01;

            //printf("speler_end A1\n");
        } else if ((streamA << y) & 0x80) {
            speler = speler | 0x01;
            speler = speler << 1;

            //printf("speler A1\n");
        } else {
            if (y == 5) {
                //printf("speler_end A0\n");

            } else {
                speler = speler << 1;

                //printf("speler A0\n");
            }
        }
    }
    // printf("\n%d speler\n\n", speler);

    for (int y = 6; y < 11; y++) {
        if (y > 7) {
            if (((streamB << (y - 8)) & 0x80) && y == 10) {
                data = data | 0x01;
                // printf("data_end B1\n");
            } else if ((streamB << (y - 8)) & 0x80) {
                data = data | 0x01;
                data = data << 1;
                //printf("data B1\n");
            } else {
                if (y == 10) {
                    //printf("data_end B0\n");
                } else {
                    data = data << 1;
                    //printf("data B0\n");
                }

            }
        } else {
            if ((streamA << y) & 0x80) {
                data = data | 0x01;
                data = data << 1;
                //printf("data A1\n");
            } else {
                data = data << 1;
                //printf("data A0\n");
            }
        }
    }

    //printf("\n%d data\n\n", data);


    for (int y = 11; y < 16; y++) {
        if (((streamB << (y - 8)) & 0x80) && y == 15) {
            control = control | 0x01;
            //printf("control_end B1\n");
        } else if ((streamB << (y - 8)) & 0x80) {
            control = control | 0x01;
            control = control << 1;
            //printf("control B1\n");
        } else {
            if (y == 15) {
                //printf("control_end B0\n");
            } else {
                control = control << 1;
                //printf("control B0\n");
            }
        }
    }

    // hwlib::cout << "print_binaries of speler ";
    //print_binary(speler, 8);
    //hwlib::cout << "\n";
    //hwlib::cout << "print_binaries of data ";
    //print_binary(data, 8);
    // hwlib::cout << "\n";
    // hwlib::cout << "print_binaries of control ";
    //print_binary(control, 8);
    // hwlib::cout << "\n";
    //hwlib::cout<< "\nspeler " << a << "\ndata  " << b << "\ncontrol  " << c << "\n";
    write_detected_ir(speler, data, control);


    // hier komt iets van channel.write shot data

}

void IRReceiver::print_binary(char print, int lenght) {

    for (int h = 0; h < lenght; h++) {
        if ((print << h) & 0x80) {
            //std::cout<< "1";
            hwlib::cout << "1";
        } else {
            hwlib::cout << "0";
            //printf("0");
        }
    }
    //printf("\n");
}

