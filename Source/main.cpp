/**
 * \mainpage Lasergaming on arduino using RTOS
 *
 * \section intro Introduction
 *
 * We have made this project as an assignment for the Hogeschool Utrecht. We used the RTOS library of Wouter van Ooijen.\n
 * With this we have created over a span of time of 3 weeks a lasergame prototype/proof of concept on the arduino\n
 * due. With this project we also did research on several other RTOS systems. Our conclusion was that the RTOS provided\n
 * by the HU was the best one to use in this project. We also have made a solution architecture for this system. This\n
 * contains a state transition diagram, class diagram, concurrency diagram and a task structure.\n
 *\n
 * Made by: David Driessen, Jeremy Ruizenaar, Max Beunk and Mike Hilhorst.
 */
#include "bmptk.h"
#include "hwlib.hpp"
#include "rtos.hpp"

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

    //end key

    //start speaker
    auto lsp = target::pin_out(target::pins::d7);

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
    auto Speaker = SpeakerController(6,"SpeakerController", lsp);
    auto display = DisplayController(7, "DisplayController", oled);
    GameController *gameController = 0;
    auto sender = IRSender(ir, 1, "IRSender");
    auto init = InitController(sender);
    auto gameTimer = GameTimeController(4, "GameTimeController", gameController, display);
    auto temp = GameController(gameTimer, Speaker, display, sender, 3, "GameController");
    auto button = ButtonController(2, "ButtonController", temp, btn);
    gameController = &temp;
    auto receiver = IRReceiver(tsop_signal, 0, "IRReceiver", *gameController);
    auto keypad = KeyPadController(5, "KeyPadController", init, key, display);

    display.test();

    rtos::run();
    return 69;
}