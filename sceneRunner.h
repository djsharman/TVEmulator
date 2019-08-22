/**
 * Runs a current "scene"
 * 
 * A scene is the currently selected RGB values 
 * and the fade durations
 * 
 */

#include <stdio.h>
#include <wiringPi.h>
#include <piFace.h>
#include <stdint.h>
#include "ledValueSelect.h"

class sceneRunner {

    public: 
        uint8_t  rIntensity, gIntensity, bIntensity;
        uint16_t r, g, b, i;
        
        void runCurrentScene(ledValueSelect valueSelect);

    private:
        uint32_t totalTime, fadeTime, holdTime, startTime, elapsed;
        auto getTime();
        int randomNum(int min_num, int max_num);
        void sendValuesWithThreads(uint16_t r, uint16_t g, uint16_t b);
        static long map(long x, long in_min, long in_max, long out_min, long out_max);
        static uint16_t getFinalIntensity(uint16_t input);
        static void sendToPWN(uint16_t targetIntensity, int piFacePin);

};