//
// Created by david on 10/28/2016.
//

#include "DisplayController.hpp"

DisplayController::DisplayController(unsigned int priority, const char *name, hwlib::glcd_oled_buffered &display) :
        task(priority, name),
        display(display),
        time_pool("Display_time_pool"),
        bullets_pool("Display_bullets_pool"),
        weapon_pool("Display_weapon_pool"),
        playerid_pool("Display_playerid_pool"),
        update(this, "Display_update") {
}

void DisplayController::test() {
    display.clear();
    display.flush();
    hwlib::wait_ms(60 * 1);
    for (int x = 0; x < 128; ++x) {
        for (int y = 0; y < 64; ++y) {
            display.write(hwlib::location(x, y));
        }
    }
    display.flush();
    hwlib::wait_ms(60 * 3);
    display.clear();
    display.flush();
}

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
        if (master_pool.read() > 0) {
            mainMaster();
        }
        top << "\f"
            << "Time: " << time_pool.read() << "\n"
            << "______________" << "\n";

        if (hitBool) {
            middel << "\f"
                   << "  HIT" << "\n"
                   << "" << "\n";
        } else {
            if (bullets_pool.read() == 0) {

                middel << "\f"
                       << "             \n"
                       << "Mag: R\n";
            } else {
                middel << "\f"
                       << "             \n"
                       << "Mag: " << bullets_pool.read() << "\n";
            }
        }
        bottom << "\f"
               << "______________\n"
               << "ID: " << playerid_pool.read() << " W:" << weapon_pool.read() << "\n";
        display.flush();
        wait(update);
    }
}

void DisplayController::mainMaster() {
    auto font8 = hwlib::font_default_8x8();

    auto wtop = hwlib::window_part(display,
                                   hwlib::location(0, 0),
                                   hwlib::location(128, 16));
    auto top = hwlib::window_ostream(wtop, font8);
    auto wmiddel = hwlib::window_part(display,
                                      hwlib::location(0, 16),
                                      hwlib::location(128, 48));
    auto body = hwlib::window_ostream(wmiddel, font8);

    top << "\fmaster\n";
    while (master_pool.read() > 0) {
        if (master_pool.read() == 1) {
            top << "\f"
                << "______________\n"
                << "\n";

            body << "\f"
                 << "A. Player\n"
                 << "B. Weapon\n"
                 << "C. Command\n"
                 << "______________\n";
        } else if (master_pool.read() == 2) {
            top << "\f"
                << "______________" << "\n"
                << "\n";

            body << "\f"
                 << "Player: " << playerid_pool.read() << "\n"
                 << "\n"
                 << "\n"
                 << "______________" << "\n";
        } else if (master_pool.read() == 3) {
            top << "\f"
                << "______________" << "\n"
                << "\n";

            body << "\f"
                 << "Weapon: " << weapon_pool.read() << "\n"
                 << "\n"
                 << "\n"
                 << "______________" << "\n";
        } else if (master_pool.read() == 4) {
            top << "\f"
                << "______________" << "\n"
                << "\n";

            body << "\f"
                 << "Command: " << command_pool.read() << "\n"
                 << "\n"
                 << "\n"
                 << "______________" << "\n";
        } else if (master_pool.read() == 5) {
            top << "\f"
                << "______________" << "\n"
                << "\n";

            body << "\f"
                 << "Do you want to\n"
                 << "send the data ?\n"
                 << "\n"
                 << "______________" << "\n";
        }
        display.flush();
        wait(update);
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

void DisplayController::hit() {
    hitBool = true;
    update.set();
}

void DisplayController::hitClear() {
    hitBool = false;
    update.set();
}

void DisplayController::masterMenu() {
    master_pool.write(1);
    update.set();
}

void DisplayController::playerEdit(int id) {
    playerid_pool.write(id);
    master_pool.write(2);
    update.set();
}

void DisplayController::weaponEdit(int weaponInput) {
    weapon_pool.write(weaponInput);
    master_pool.write(3);
    update.set();
}

void DisplayController::commandEdit(int commandInput) {
    command_pool.write(commandInput);
    master_pool.write(4);
    update.set();
}

void DisplayController::confirm() {
    master_pool.write(5);
    update.set();
}

void DisplayController::end() {
    master_pool.write(0);
    update.set();
}
