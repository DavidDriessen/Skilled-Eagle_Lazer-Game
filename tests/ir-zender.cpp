#include "hwlib.hpp"

int main(void) {

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    // wait for the PC terminal to start
    hwlib::wait_ms(500);

    // IR output LED
    auto ir = hwlib::target::d2_36kHz();

    bool send[16];
    byte b[2] = {0b11010110, 0b01010110};
    
    for (int k = 0; k < 2; k++) {
        
        send[(k * 8) + 0] = (b[k] & 0b10000000) ? '1' : '0';
        send[(k * 8) + 1] = (b[k] & 0b01000000) ? '1' : '0';
        send[(k * 8) + 2] = (b[k] & 0b00100000) ? '1' : '0';
        send[(k * 8) + 3] = (b[k] & 0b00010000) ? '1' : '0';
        send[(k * 8) + 4] = (b[k] & 0b00001000) ? '1' : '0';
        send[(k * 8) + 5] = (b[k] & 0b00000100) ? '1' : '0';
        send[(k * 8) + 6] = (b[k] & 0b00000010) ? '1' : '0';
        send[(k * 8) + 7] = (b[k] & 0b00000001) ? '1' : '0';
    }

    while (1) {
        for (int i = 0; i < 16; i++) {
            if (send[i]) {
                ir.set(1);
                hwlib::wait_us(1600);

                ir.set(0);
                hwlib::wait_us(800);
            } else {
                ir.set(1);
                hwlib::wait_us(800);

                ir.set(0);
                hwlib::wait_us(1600);
            }
        }
        hwlib::wait_ms(3);
    }

}
