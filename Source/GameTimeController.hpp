//
// Created by Muxbee on 07-11-16.
//

#ifndef SKILLED_EAGLE_GAMETIMECONTROLLER_HPP
#define SKILLED_EAGLE_GAMETIMECONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "GameController.hpp"

class GameTimeController: public rtos::task<>{
    private:
        void main();
        rtos::timer gameTime;
        GameController  & gameController;

    public:
        GameTimeController(unsigned int priority,
                           const char *name,
                           GameController & gameController
        ):
                task(priority, name), gameTime(this, "gameTime"), gameController(gameController){};

        void start(unsigned long time);

        void stop();
};


#endif //SKILLED_EAGLE_GAMETIMECONTROLLER_HPP
