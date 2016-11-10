//
// Created by Muxbee on 07-11-16.
//

#ifndef SKILLED_EAGLE_GAMETIMECONTROLLER_HPP
#define SKILLED_EAGLE_GAMETIMECONTROLLER_HPP

class GameController;

#include "hwlib.hpp"
#include "rtos.hpp"
#include "GameController.hpp"
#include "DisplayController.hpp"


class GameTimeController: public rtos::task<>{
    private:
        void main();
        rtos::timer updateTime;
        GameController  * gameController;
        DisplayController & displayController;
        unsigned long time;

    public:
        GameTimeController(unsigned int priority,
                           const char *name,
                           GameController * gameController,
                           DisplayController & displayController
        ):
                task(priority, name), updateTime(this, "updateTime"), gameController(gameController), displayController(displayController){};

        void start(unsigned long time);

        void stop();
};


#endif //SKILLED_EAGLE_GAMETIMECONTROLLER_HPP
