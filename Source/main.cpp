#include "bmptk.h"
#include "hwlib.hpp"
#include "rtos.hpp"

#define Display_test

#include "IRReceiver.hpp"
#include "KeyPadController.hpp"
#include "ButtonController.hpp"

int main() {
    hwlib::wait_ms(500);
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    namespace target = hwlib::target;
    //key pins (start)
    auto out0 = target::pin_oc(target::pins::a0);
    auto out1 = target::pin_oc(target::pins::a1);
    auto out2 = target::pin_oc(target::pins::a2);
    auto out3 = target::pin_oc(target::pins::a3);

    auto in0 = target::pin_in(target::pins::a4);
    auto in1 = target::pin_in(target::pins::a5);
    auto in2 = target::pin_in(target::pins::a6);
    auto in3 = target::pin_in(target::pins::a7);

    auto out_port = hwlib::port_oc_from_pins(out0, out1, out2, out3);
    auto in_port = hwlib::port_in_from_pins(in0, in1, in2, in3);
    auto matrix = hwlib::matrix_of_switches(out_port, in_port);
    auto key = hwlib::keypad<16>(matrix, "123A456B789C*0#D");
    auto init = InitController();
    //end key

    //start speaker
    auto lsp = target::pin_out(target::pins::d7);
    auto Speaker = SpeakerController(lsp);
    //end speaker

    //ir start
    auto ir = target::d2_36kHz();
    auto tsop_signal = target::pin_in(target::pins::d8);
    //end ir

    //OLED start
    auto scl = target::pin_oc(target::pins::scl);
    auto sda = target::pin_oc(target::pins::sda);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    auto oled = hwlib::glcd_oled_buffered(i2c_bus, 0x3c);

    //OLED stop

    //button
    auto btn = target::pin_in(target::pins::d6);

    //start rtos
    auto display = DisplayController(6, "DisplayController", oled);
    GameController *gameController = 0;
    auto sender = IRSender(ir, 1, "IRSender");
    auto gameTimer = GameTimeController(4, "GameTimeController", gameController, display);
    auto temp = GameController(gameTimer, Speaker, display, sender, 3, "GameController");
    auto button = ButtonController(2, "ButtonController", temp, btn);
    gameController = &temp;
    auto receiver = IRReceiver(tsop_signal, 0, "IRReceiver", *gameController);
    auto keypad = KeyPadController(5, "KeyPadController", init, key, display);

    rtos::run();
    return 69;
}