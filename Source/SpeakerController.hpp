//
// Created by MuscioCraft on 8-11-2016.
//

#ifndef SKILLED_EAGLE_SPEAKERCONTROLLER_HPP
#define SKILLED_EAGLE_SPEAKERCONTROLLER_HPP
#include "hwlib.hpp"

class SpeakerController {
private:
    hwlib::pin_out & lsp;
    void await( long long int t );
    void beep(int f, int d, int fd);
public:
    SpeakerController(hwlib::pin_out & lsp):
    lsp(lsp){};


    void peew();
    void beep3();
    void ohhh();
    void uhoh();
    void noise();
    void noise2();
    void click();


};



#endif //SKILLED_EAGLE_SPEAKERCONTROLLER_HPP


