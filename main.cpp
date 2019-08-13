#include <stdio.h>
#include <wiringPi.h>
#include <piFace.h>
//#include <iostream>

#include "ledValueSelect.h"


#define PIFACE 200
#define LED (PIFACE + 2)

int main(int argc, char** argv)
{
    printf("Starting Up TV Emulator\n");
    printf("=========================\n");

    wiringPiSetupSys();

    // Setup the PiFace board

    piFaceSetup(PIFACE);

    ledValueSelect valueSelect;

    valueSelect.selectNextValue();




    printf( "NR: %X\n", valueSelect.nr);
    printf( "NG: %X\n", valueSelect.ng);
    printf("=========================\n");

    return 0;
}