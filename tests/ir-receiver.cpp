#include "hwlib.hpp"

#define RESOLUTION 20
#define MAXPULSE 1700 / RESOLUTION
#define MINPULSE 300 / RESOLUTION
#define THRESHOLD 900
int pulses[100];
int currentpulse = 0;
bool debug = 0;

void printpulses(void) {
    if (debug) {
        hwlib::cout << "\n\r\n\rReceived: \n\rOFF \tON\n";
        for (int i = 0; i < currentpulse; i++) {
            hwlib::cout << pulses[i] * RESOLUTION;
            hwlib::cout << " usec\n";
        }
    } else {
        for (int i = 0; i < currentpulse; i++) {
            if (pulses[i] * RESOLUTION > THRESHOLD) {
                hwlib::cout << "1\n";
            } else if (pulses[i] * RESOLUTION < THRESHOLD) {
                hwlib::cout << "0\n";
            } else {
                hwlib::cout << "NOOOO\n";
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

    tsop_gnd.set(0);
    tsop_vdd.set(1);

    int pulse = 0;

    while (currentpulse < 16) {
        // terwijl het signaal uit de decoder hoog is
        while (tsop_signal.get() == 0) {
            // verhoog tijd variabele en wacht aantal us
            pulse++;
            hwlib::wait_us(RESOLUTION);
            // als deze pulse langer duurd dan time out
            // reset
            if ((pulse >= MAXPULSE)) {
                currentpulse = 0;
                pulse = 0;
            }
        }
        if (pulse <= MINPULSE) {
            currentpulse = 0;
            continue;
        }
        // sla de pulse op in het pulse array
        pulses[currentpulse] = pulse;
        // verhoog positie in pulse array
        currentpulse++;
        // zet de timing variabelen op 0
        pulse = 0;
    }
    printpulses();
}
