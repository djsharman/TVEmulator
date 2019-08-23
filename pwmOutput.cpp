
#include "pwmOutput.h"
#include <wiringPi.h>
#include <piFace.h>



void pwmOutput::outputCurrentTimeSlice(int i, int piFacePin) {

    if(i >= 10) {
        digitalWrite(piFacePin, HIGH); // On
        delayMicroseconds(i * 10);
        digitalWrite(piFacePin, LOW); // Off
    }
    delayMicroseconds((500 - i) * 10);

}