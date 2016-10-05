#include "hwlib.hpp"

#define RESOLUTION 200
#define MAXPULSE 2000 / RESOLUTION
#define MINPULSE 300 / RESOLUTION
int pulses[100][2];
int currentpulse = 0;
bool print = 0;

void printpulses(void) {
    if (print) {
        hwlib::cout << "\n\r\n\rReceived: \n\rOFF \tON\n";
        for (int i = 0; i < currentpulse; i++) {
            hwlib::cout << pulses[i][0] * RESOLUTION;  //verwissel deze 0 en 1 om positie van high and low te wissellen
            hwlib::cout << " usec, ";
            hwlib::cout << pulses[i][1] * RESOLUTION;
            hwlib::cout << " usec\n";
        }
    } else {
        for (int i = 0; i < currentpulse; i++) {
            if (pulses[i][1] * RESOLUTION > 1000) {
                hwlib::cout << "1";
            } else if (pulses[i][1] * RESOLUTION < 1000) {
                hwlib::cout << "0";
            } else {
                hwlib::cout << " ";
            }
        }
        hwlib::cout << currentpulse << "\n";
    }
}


int main(void) {
    hwlib::wait_ms(500);
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    namespace target = hwlib::target;

    auto tsop_signal = target::pin_in(target::pins::d8);
    auto tsop_gnd = target::pin_out(target::pins::d9);
    auto tsop_vdd = target::pin_out(target::pins::d10);

    ///kruislings lezen


    tsop_gnd.set(0);
    tsop_vdd.set(1);


    int highpulse, lowpulse;
    highpulse = lowpulse = 0;

    while (currentpulse < 16) {
        // zet de timing variabelen op 0
        highpulse = lowpulse = 0;
        // terwijl het signaal uit de decoder laag is
        while (tsop_signal.get() == 1) {
            // verhoog tijd variabele en wacht aantal us
            highpulse++;
            hwlib::wait_us(RESOLUTION);
            // als deze pulse langer duurd dan time out en er is 1 pulse gezien
            // print de pulsen en return
            if ((highpulse >= MAXPULSE)) {
                currentpulse = 0;
            }
        }
        if (highpulse < MINPULSE) {
            currentpulse = 0;
        }
        // sla de pulse op in het pulse array
        pulses[currentpulse][0] = highpulse;
        // terwijl het signaal uit de decoder hoog is
        while (tsop_signal.get() == 0) {
            // verhoog tijd variabele en wacht aantal us
            lowpulse++;
            hwlib::wait_us(RESOLUTION);
            // als deze pulse langer duurd dan time out en er is 1 pulse gezien
            // print de pulsen en return
            if ((lowpulse >= MAXPULSE)) {
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
