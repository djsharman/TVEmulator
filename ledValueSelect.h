#pragma once
#include <stdio.h>
#include <wiringPi.h>
#include <piFace.h>
#include <stdint.h>
//#include <iostream>

using namespace std;

class ledValueSelect {

    public: 

        uint32_t totalTime, fadeTime, holdTime, startTime, elapsed;
        uint16_t nr = 0, ng = 0, nb = 0; // new color values
        uint16_t pr, pg, pb; // previous color values
        uint8_t  hi, lo, r8, g8, b8;

        uint16_t gammaSize, colourSize;

        uint32_t pixelNum;


        ledValueSelect();

        int randomNum(int min_num, int max_num);

        void selectNextValue();
    

};