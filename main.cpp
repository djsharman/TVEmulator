#include <stdio.h>
#include <wiringPi.h>
#include <piFace.h>
//#include <iostream>

#include "ledValueSelect.h"
#include "sceneRunner.h"


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
    sceneRunner runner;


    for(;;) {
        valueSelect.selectNextValue();
        runner.runCurrentScene(valueSelect);
    }



    return 0;
}
