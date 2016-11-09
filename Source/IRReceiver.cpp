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
#if debug > 0
        printpulses();
<<<<<<< HEAD
        hwlib::wait_us(3000);
=======
#endif
>>>>>>> c52ff84fc340df722568f7343c31582cf5c08956
    }
}
