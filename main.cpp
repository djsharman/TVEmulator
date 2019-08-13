#include <stdio.h>
#include <wiringPi.h>
#include <piFace.h>
//#include <iostream>
#include "tvParams.h"


#define PIFACE 200
#define LED (PIFACE + 2)

int main(int argc, char** argv)
{
    printf("Starting Up TV Emulator\n");
    printf("=========================\n");

    // Always initialise wiringPi. Use wiringPiSys() if you don't need
    //      (or want) to run as root

    unsigned int postion = 5;

    unsigned int gammaSize = tvParams::getGammaSize();
    unsigned int colourSize = tvParams::getColorSize();

    //unsigned char a = tvParams::getGamma(postion);

    printf( "gammaSize: %X\n", gammaSize);
    printf( "colorSize: %X\n", colourSize);
    printf("=========================\n");

    wiringPiSetupSys();

    // Setup the PiFace board

    piFaceSetup(PIFACE);

    int i;
    int z;

    while (1) {
        for (i = 0; i < 500; i++) {
            for (z = 0; z < 1; z++) {

                digitalWrite(LED, HIGH); // On
                delayMicroseconds(i * 10);
                digitalWrite(LED, LOW); // Off
                delayMicroseconds((500 - i) * 10);
            };
        };
        for (i = 500; i > 0; i--) {
            for (z = 0; z < 1; z++) {

                digitalWrite(LED, HIGH); // On
                delayMicroseconds(i * 10);
                digitalWrite(LED, LOW); // Off
                delayMicroseconds((500 - i) * 10);
            };
        };
    }

    return 0;
}