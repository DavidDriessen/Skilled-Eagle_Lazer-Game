//
// Created by david on 10/5/2016.
//

#include "IRReceiver.hpp"

void IRReceiver::printpulses(void)
{
    if (debug) {
        hwlib::cout << "\n\r\n\rReceived: \n\rOFF \tON\n";
        for (int i = 0; i < currentpulse; i++) {
            hwlib::cout << pulses[i][0] * RESOLUTION;  //verwissel deze 0 en 1 om positie van high and low te wissellen
            hwlib::cout << " usec, ";
            hwlib::cout << pulses[i][1] * RESOLUTION;
            hwlib::cout << " usec\n";
        }
    } else {
        for (int i = 0; i < currentpulse; i++) {
            if (pulses[i][1] * RESOLUTION > 900) {
                hwlib::cout << "1";
            } else {
                hwlib::cout << "0";
            }
        }
        hwlib::cout << "\n";
    }
}

void IRReceiver::main() {
    while(1) {
        currentpulse = 0;
        while (currentpulse < 16) {
            // zet de timing variabelen op 0
            highpulse = lowpulse = 0;
            // terwijl het signaal uit de decoder laag is
            while (tsop_signal.get() == 0) {
                // verhoog tijd variabele en wacht aantal us
                highpulse++;
                interval.set(RESOLUTION);
                wait(interval);
                // als deze pulse langer duurd dan time out en er is 1 pulse gezien
                // print de pulsen en return
                if (highpulse >= MAXPULSE) {
                    currentpulse = 0;
                }
            }
            if (highpulse < MINPULSE) {
                currentpulse = 0;
            }
            // sla de pulse op in het pulse array
            pulses[currentpulse][0] = highpulse;
            // terwijl het signaal uit de decoder hoog is
            while (tsop_signal.get() == 1) {
                // verhoog tijd variabele en wacht aantal us
                lowpulse++;
                interval.set(RESOLUTION);
                wait(interval);
                // als deze pulse langer duurd dan time out en er is 1 pulse gezien
                // print de pulsen en return
                if (lowpulse >= MAXPULSE) {
                    currentpulse = 0;
                }
            }
            if (lowpulse < MINPULSE) {
                currentpulse = 0;
            }
            // sla de pulse op in het pulse array
            pulses[currentpulse][1] = lowpulse;
            // verhoog positie in pulse array
            currentpulse++;
        }
        printpulses();
    }
}
