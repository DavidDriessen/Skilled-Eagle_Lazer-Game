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

/**
 * The function test the display for bad pixels.
 *
 * */

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
    hwlib::wait_ms(60 * 5);
    display.clear();
    display.flush();
}

/**
 * Shows the player his info, such as weapon, player_ID and remeaning time and bullets on the display.
 */

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
                   << "         " << "\n";
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
               << "ID: " << playerid_pool.read() << " W:" << GetWeaponName(weapon_pool.read()) << "\n";
        display.flush();
        wait(update);
    }
}

/**
 * Shows the master menu and the settings screens for player_ID, weapon and command.
 */

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
                 << "Weapon: " << GetWeaponName(weapon_pool.read()) << "\n"
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

/**
 * Updates the time on the display.
 * @param time_in_minutes
 */

void DisplayController::setTime(int time_in_minutes) {
    if (time_in_minutes < 0) {
        time_in_minutes = 0;
    }
    time_pool.write(time_in_minutes);
    update.set();
}

/**
 * Updates the anount of bullets left.
 * @param number_of_bullets
 */

void DisplayController::setBullets(int number_of_bullets) {
    bullets_pool.write(number_of_bullets);
    update.set();
}

/**
 * Updates the weapon shown on the display.
 * @param weapon
 */

void DisplayController::setWeapon(Weapons weapon) {
    weapon_pool.write((int) weapon);
    update.set();
}

/**
 * Updates the player_ID shown on the display.
 * @param player_ID
 */

void DisplayController::setPlayerId(int player_ID) {
    playerid_pool.write(player_ID);
    update.set();
}

/**
 * Show the player that he is hit.
 */

void DisplayController::hit() {
    hitBool = true;
    update.set();
}

/**
 * Show the player that he can play again.
 */

void DisplayController::hitClear() {
    hitBool = false;
    update.set();
}

/**
 * Displays the master menu.
 */

void DisplayController::masterMenu() {
    master_pool.write(1);
    update.set();
}

/**
 * Update player_ID for master in player settings page.
 * @param id
 */

void DisplayController::playerEdit(int id) {
    playerid_pool.write(id);
    master_pool.write(2);
    update.set();
}

/**
 * Update weapon for master in weapon settings page.
 * @param weapon_ID
 */

void DisplayController::weaponEdit(int weapon_ID) {
    weapon_pool.write(weapon_ID);
    master_pool.write(3);
    update.set();
}

/**
 * Update command id for master in command settings page.
 * @param weapon_ID
 */

void DisplayController::commandEdit(int commandInput) {
    command_pool.write(commandInput);
    master_pool.write(4);
    update.set();
}

/**
 * Ask for confirmation to send the command.
 */

void DisplayController::confirm() {
    master_pool.write(5);
    update.set();
}

/**
 * Show the player screen.
 */

void DisplayController::end() {
    master_pool.write(0);
    update.set();
}
