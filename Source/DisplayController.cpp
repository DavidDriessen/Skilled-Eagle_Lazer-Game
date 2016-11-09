//
// Created by david on 10/28/2016.
//

#include "DisplayController.hpp"
int master = 0;

void DisplayController::main() {
//#define isMaster
#ifdef isMaster
//    auto font16 = hwlib::font_default_16x16();
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
    while (1) {
        if (master == 0) {
            body << "\f" << "A. player\n" << "B. Weapon\n" << "C. command\n";
        }

        display.flush();
        wait(update);
    }
#else
    //auto font16 = hwlib::font_default_16x16();
    auto font8 = hwlib::font_default_8x8();

    auto wtop = hwlib::window_part(display,
                                   hwlib::location(0, 0),
                                   hwlib::location(128, 16));
    auto top = hwlib::window_ostream(wtop, font8);
    auto wmiddel = hwlib::window_part(display,
                                      hwlib::location(0, 16),
                                      hwlib::location(128, 32));
    auto middel = hwlib::window_ostream(wmiddel, font8);
    auto wbottom = hwlib::window_part(display,
                                      hwlib::location(0, 48),
                                      hwlib::location(128, 32));
    auto bottom = hwlib::window_ostream(wbottom, font8);
   /* while (1) {
        top << "\f"
            << "Time: " << time << "\n"
            << "______________" << "\n";

        if (hitBool) {
            middel << "\f"
                   << "  HIT" << "\n"
                   << "" << "\n";
        } else {
            middel << "\f"
                   << "             \n"
                   << "Mag: " << bullets << "\n";
        }
        bottom << "\f"
               << "______________\n"
               << "ID: " << playerid << " W:" << weapon << "\n";
        display.flush();
        wait(update);
    }*/

while (1) {
    if(master==0)
    {
        top << "\f"
            << "Time: " << time << "\n"
            << "______________" << "\n";

        if (hitBool) {
            middel << "\f"
                   << "  HIT" << "\n"
                   << "" << "\n";
        } else {
            middel << "\f"
                   << "             \n"
                   << "Mag: " << bullets << "\n";
        }
        bottom << "\f"
               << "______________\n"
               << "ID: " << player << "   W: " << weapon << "\n";
    }
    if(master==1) {
        top     << "\f"
                << "______________\n"
                << "A. Player" << "\n";

        middel  << "\f"
                << "B. Weapon\n"
                << "C. Command\n";

        bottom  << "\f"
                << "\n"
                << "______________\n";
    }

    if(master==2) {
        top << "\f"
            << "______________" << "\n"
            << "\n";

        middel << "\f"
               << "Player: " << player << "\n"
               << "\n";

        bottom << "\f"
               << "\n"
               << "______________" << "\n";
    }

    if(master==3) {
        top << "\f"
            << "______________" << "\n"
            << "\n";

        middel << "\f"
               << "Weapon: " << weapon << "\n"
               << "\n";

        bottom << "\f"
               << "\n"
               << "______________" << "\n";
    }
    if(master==4) {
        top << "\f"
            << "______________" << "\n"
            << "\n";

        middel << "\f"
               << "Command: " << command << "\n"
               << "\n";

        bottom << "\f"
               << "\n"
               << "______________" << "\n";
    }
    if(master==5) {
        top << "\f"
            << "______________" << "\n"
            << "\n";

        middel << "\f"
               << "Do you want to\n"
               << "send the data ?\n";

        bottom << "\f"
               << "\n"
               << "______________" << "\n";
    }
    display.flush();
    wait(update);
}



#endif

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
    master = 1;
    update.set();
}

void DisplayController::playerEdit(int id) {
    player = id;
    master = 2;
    update.set();
}

void DisplayController::weaponEdit(int weaponInput) {
    weapon = weaponInput;
    master = 3;
    update.set();
}

void DisplayController::commandEdit(int commandInput) {
    command = commandInput;
    master = 4;
    update.set();
}

void DisplayController::confirm() {
    master = 5;
    update.set();
}

void DisplayController::end(){
    master = 0;
    update.set();
}

