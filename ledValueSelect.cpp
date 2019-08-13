#include <stdio.h>
//#include <iostream>
#include "ledValueSelect.h"
#include "tvParams.h"
#include <iostream>
#include <random>

using namespace std;

ledValueSelect::ledValueSelect() {

    printf("In LED Value select constructor\n");
    printf("=========================\n");


    
    gammaSize = tvParams::getGammaSize();
    colourSize = tvParams::getColorSize();

    pixelNum = randomNum(0, (colourSize - 1));

    printf( "gammaSize: %X\n", gammaSize);
    printf( "colourSize: %X\n", colourSize);
    printf( "pixelNum: %X\n", pixelNum);
    printf("=========================\n");
}

int ledValueSelect::randomNum(int min_num, int max_num) {
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(min_num, max_num);
    return distr(eng);
}


void ledValueSelect::selectNextValue() {


    // Read next 16-bit (5/6/5) color

    hi =  tvParams::getColor(pixelNum);
    lo =  tvParams::getColor(pixelNum +1);

    // Expand to 24-bit (8/8/8)
    r8 = (hi & 0xF8) | (hi >> 5);
    g8 = (hi << 5) | ((lo & 0xE0) >> 3) | ((hi & 0x06) >> 1);
    b8 = (lo << 3) | ((lo & 0x1F) >> 2);


    // Apply gamma correction, further expand to 16/16/16
    nr = (uint8_t)tvParams::getGamma(r8) * 257; // New R/G/B
    ng = (uint8_t)tvParams::getGamma(g8) * 257;
    nb = (uint8_t)tvParams::getGamma(b8) * 257;

    totalTime = randomNum(250, 2500);    // Semi-random pixel-to-pixel time
    fadeTime  = randomNum(0, totalTime); // Pixel-to-pixel transition time
    if(randomNum(0, 10) < 3) fadeTime = 0;  // Force scene cut 30% of time
    holdTime  = totalTime - fadeTime; // Non-transition time

    pixelNum += 2;
    if(pixelNum >= colourSize) {
        pixelNum = 0;
    }

}