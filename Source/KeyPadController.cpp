//
// Created by MuscioCraft on 7-11-2016.
//

#include "KeyPadController.hpp"


void KeyPadController::main() {
    int n = 0;
    int numbers[100];
    int a_condition = 0;
    int a_input_array_size = 0;
    int player=1;
    int weapon=0;


    for(;;)
    {
        cout << "\nA: Set player\nB: Weapon power selector\nC: End command\n\n";
        auto c = keypad.getc();

        if(c=='#')
        {
            cout << "\nEnd\n";
            break;
        }
        // A Selecteerd Speler
        if(c=='A')
        {
            cout << "Welke speler?";
            while(a_condition==0)
            {
                auto t = keypad.getc();
                if(t >= '1' && t <= '9') {
                    numbers[n]=t-'0'; // ascii to int
                    cout << numbers[n];
                    a_input_array_size++;
                    n++;
                }
                //stop
                if(t == '#'){a_condition = 1;}
                KeyTimer.set(100*rtos::ms);
                wait(KeyTimer);
            }

            player = array_to_intger(numbers, a_input_array_size);
            cout << "\nU bent speler: " << player <<"\n";


        }

        if(c=='B')
        {
            cout << "Welk wapen wilt u gebruiken ?\n";


            cout << static_cast<int>(Weapons::AK47)     << ". AK47"   << "\n";
            cout << static_cast<int>(Weapons::M9)       << ". M9"     << "\n";
            cout << static_cast<int>(Weapons::MP5)      << ". MP5"    << "\n";
            cout << static_cast<int>(Weapons::UZI)      << ". UZI"    << "\n";
            cout << static_cast<int>(Weapons::PARKER)   << ". PARKER" << "\n";
            cout << static_cast<int>(Weapons::IPOD)     << ". IPOD"   << "\n";
            cout << static_cast<int>(Weapons::RPG)      << ". RPG"    << "\n";
            cout << static_cast<int>(Weapons::TIMMY)    << ". TIMMY"  << "\n";
            cout << static_cast<int>(Weapons::JIMMY)    << ". JIMMY"  << "\n";

            cout << "\n> ";

            auto t = keypad.getc();
            weapon = t -48;
            cout << weapon << "\n";


            if(t==static_cast<char>(Weapons::AK47)  +48) {
                cout << "AN-94\n";
                for (int i = 0; i < 3; i++)
                {
                    speak.click();
                    hwlib::wait_ms(200);
                }
            }
            if(t==static_cast<char>(Weapons::M9)    +48){
                cout << "AN-94\n";
                for (int i = 0; i < 1; i++)
                {
                    speak.peew();
                    hwlib::wait_ms(100);}
            }
            if(t==static_cast<char>(Weapons::MP5)   +48){cout << "Remington 870 MCS\n";}
            if(t==static_cast<char>(Weapons::UZI)   +48){cout << "DSR 50\n";}
            if(t==static_cast<char>(Weapons::PARKER)+48){cout << "PDW-57\n";}
            if(t==static_cast<char>(Weapons::IPOD)  +48){cout << "Scar-H\n";}
            if(t==static_cast<char>(Weapons::RPG)   +48){cout << "BALLISTA\n";}
            if(t==static_cast<char>(Weapons::TIMMY) +48){cout << "Peacekeeper\n";}
            if(t==static_cast<char>(Weapons::JIMMY) +48){cout << "M27\n";}
        }

        if(c=='C'){cout << "Ping\n";}
        if(c=='D'){cout << "Pong\n";}
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

