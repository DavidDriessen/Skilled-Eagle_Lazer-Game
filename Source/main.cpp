#include "bmptk.h"
#include "hwlib.hpp"
#include "rtos.hpp"

#include "IRReceiver.hpp"
#include "IRSender.hpp"

int main() {
    hwlib::wait_ms(500);
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    namespace target = hwlib::target;

    auto ir = hwlib::target::d2_36kHz();
    auto tsop_signal = target::pin_in(target::pins::d8);

    auto display = DisplayController(2, "DisplayController");
    auto receiver = IRReceiver(tsop_signal, 0, "IRReceiver", display);
    auto zender = IRSender(ir, 1, "IRSender");

    rtos::run();
    return 0;
}