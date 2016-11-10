//
// Created by MuscioCraft on 7-11-2016.
//

#include "KeyPadController.hpp"

//! The main
void KeyPadController::main() {
    int a_n = 0;            //! Array walker for A
    int c_n = 0;            //! Array walker for C
    int a_numbers[100];     //! Array for A
    int c_numbers[100];     //! Array for C
    int a_condition = 0;    //! While loop breaker for A
    int c_condition = 0;    //! While loop breaker for C
    int a_input_array_size = 0; //! Array size A
    int c_input_array_size = 0;  //! Array size C

    while (1) {
        auto c = keypad.getc();

        if (c == 'A') {
            display.playerEdit(0);
            while (a_condition == 0) {              //! 
                auto t = keypad.getc();
                if (t >= '0' && t <= '9') {
                    a_numbers[a_n] = t - '0';
                    a_input_array_size++;
                    display.playerEdit(array_to_intger(a_numbers, a_input_array_size));
                    a_n++;
                }
                if (t == '#') {
                    a_condition = 1;
                }
                KeyTimer.set(100 * rtos::ms);
                wait(KeyTimer);
            }
            init.PlayerGetter(array_to_intger(a_numbers, a_input_array_size));
            display.masterMenu();
        } else if (c == 'B') {
            display.weaponEdit(0);
            auto t = keypad.getc();
            init.WeaponGetter(t - 48);
            display.weaponEdit(t - 48);
            display.masterMenu();
        } else if (c == 'C') {
            display.commandEdit(0);
            while (c_condition == 0) {
                auto t = keypad.getc();
                if (t >= '0' && t <= '9') {
                    c_numbers[c_n] = t - '0';
                    c_input_array_size++;
                    display.commandEdit(array_to_intger(c_numbers, c_input_array_size));
                    c_n++;
                }
                if (t == '#') {
                    c_condition = 1;
                }
                KeyTimer.set(100 * rtos::ms);
                wait(KeyTimer);
            }

            init.CommandGetter(array_to_intger(c_numbers, c_input_array_size));
            c_condition = 0;

            while (c_condition == 0) {
                display.confirm();
                auto t = keypad.getc();
                if (t == '#') {
                    display.end();

                    c_condition = 1;

                }
                KeyTimer.set(100 * rtos::ms);
                wait(KeyTimer);
            }
        } else if (c == 'D') {
            display.masterMenu();
        }
        KeyTimer.set(100 * rtos::ms);
        wait(KeyTimer);
    }
}

//! Array to Intger
/**
 * This function make from a array a intger
 * Exemple array = {1,2,3}
 * int test = array_to_intger(array, 3)
 * test = 123
 * */
int KeyPadController::array_to_intger(int *content, int array_size) {
    int finalNumber = 0;
    int tmp = 0;
    for (int i = 0; i < array_size; i++) {
        tmp = content[i];
        if (tmp != 0) {
            while (tmp > 0) {
                finalNumber *= 10;
                tmp /= 10;
            }
            finalNumber += content[i];
        } else {
            finalNumber *= 10;
        }
    }
    return finalNumber;
}

