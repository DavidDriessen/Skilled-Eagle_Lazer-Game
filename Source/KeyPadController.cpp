//
// Created by MuscioCraft on 7-11-2016.
//

#include "KeyPadController.hpp"


void KeyPadController::main()
{
    int a_n = 0;
    int c_n = 0;
    int a_numbers[100];
    int c_numbers[100];
    int a_condition = 0;
    int c_condition = 0;
    int a_input_array_size = 0;
    int c_input_array_size = 0;

    while(1)
    {
        auto c = keypad.getc();

        if(c=='A')
        {
            while(a_condition==0)
            {
                auto t = keypad.getc();
                if(t >= '1' && t <= '9')
                {
                    a_numbers[a_n]=t-'0';
                    a_input_array_size++;
                    a_n++;
                }
                if(t == '#')
                {
                    a_condition = 1;
                }
                KeyTimer.set(100*rtos::ms);
                wait(KeyTimer);
            }
            init.PlayerGetter(array_to_intger(a_numbers, a_input_array_size));
        }

        if(c=='B')
        {
            auto t = keypad.getc();
            init.WeaponGetter(t - 48);
        }

        if(c=='C')
        {
            while (c_condition == 0)
            {
                auto t = keypad.getc();
                if (t >= '1' && t <= '9')
                {
                    c_numbers[c_n] = t - '0';
                    c_input_array_size++;
                    c_n++;
                }
                if (t == '#')
                {
                    c_condition = 1;
                }
                KeyTimer.set(100 * rtos::ms);
                wait(KeyTimer);
            }

            init.CommandGetter(array_to_intger(c_numbers, c_input_array_size));
            c_condition = 0;

            while (c_condition == 0)
            {
                auto t = keypad.getc();
                if (t == '#')
                {
                    c_condition = 1;
                }
                KeyTimer.set(100 * rtos::ms);
                wait(KeyTimer);
            }
        }
        KeyTimer.set(100*rtos::ms);
        wait(KeyTimer);
    }
}


int KeyPadController::array_to_intger(int *content, int array_size)
{
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

