#include "hwlib.hpp"
#include "rtos.hpp"
#include "IR_Receiver.hpp"
#include "IR_Zender.hpp"

int main() {
    hwlib::wait_ms(500);
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    namespace target = hwlib::target;

    auto ir = hwlib::target::d2_36kHz();
    auto tsop_signal = target::pin_in(target::pins::d8);

    auto receiver = IR_Receiver(tsop_signal, 0, "receiver");
    auto zender = IR_Zender(ir, 1, "zender");

    rtos::run();
    return 0;
}