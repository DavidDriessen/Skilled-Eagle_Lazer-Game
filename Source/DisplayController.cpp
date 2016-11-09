//
// Created by david on 10/28/2016.
//

#include "DisplayController.hpp"

void DisplayController::main() {
    auto font16 = hwlib::font_default_16x16();
    auto font8 = hwlib::font_default_8x8();

    auto wtop = hwlib::window_part(display,
                                   hwlib::location(0, 0),
                                   hwlib::location(128, 16));
    auto top = hwlib::window_ostream(wtop, font8);
    auto wmiddel = hwlib::window_part(display,
                                      hwlib::location(0, 16),
                                      hwlib::location(128, 32));
    auto middel = hwlib::window_ostream(wmiddel, font16);
    auto wbottom = hwlib::window_part(display,
                                      hwlib::location(0, 48),
                                      hwlib::location(128, 32));
    auto bottom = hwlib::window_ostream(wbottom, font8);
    while (1) {
        top << "\f"
            << "Time: " << time << "\n"
            << "______________" << "\n";
        middel << "\f"
               << "  HIT" << "\n"
               << "" << "\n";
        bottom << "\f"
               << "______________\n"
               << "ID: " << playerid << " Mag: " << bullets << "\n";
        display.flush();
        time += 5;
        bullets+=3;
        playerid++;
        hwlib::wait_ms(300);
        //wait(update);
    }

}

void DisplayController::setTime(int time) {
    time_pool.write(time);
    update.set();
}

void DisplayController::setBullets(int number) {
    bullets_pool.write(number);
    update.set();
}

void DisplayController::setWeapon(Weapons weapon) {
    weapon_pool.write((int) weapon);
    update.set();
}

void DisplayController::setPlayerId(int player) {
    playerid_pool.write(player);
    update.set();
}

