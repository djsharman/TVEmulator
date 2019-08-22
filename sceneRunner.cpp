

#include "sceneRunner.h"
#include <chrono>
#include <iostream> 
#include <random>
#include <thread>

#include "ledValueSelect.h"
#include "pwmOutput.h"

#define PIFACE 200
#define LED_R (PIFACE + 2)
#define LED_G (PIFACE + 3)
#define LED_B (PIFACE + 4)



/**
 * Get the current chrono time
 */
auto sceneRunner::getTime() {
    auto time = chrono::steady_clock::now();
    return time;
}

/**
 * Equivalent of the arduino map function
 * Maps a set of values from one rang to another
 */
long sceneRunner:: map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



int sceneRunner::randomNum(int min_num, int max_num) {
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(min_num, max_num);
    return distr(eng);
}

void sceneRunner::runCurrentScene(ledValueSelect valueSelect) {
  totalTime = randomNum(250, 2500);    // Semi-random pixel-to-pixel time
  fadeTime  = randomNum(0, totalTime); // Pixel-to-pixel transition time
  
  if(randomNum(0, 10) < 3) fadeTime = 0;  // Force scene cut 30% of time
  
  holdTime  = totalTime - fadeTime; // Non-transition time

  auto startTime = getTime();

  // fade time between colors
  for(;;) {
    auto curTime = getTime();

    // get elapsed time in microseconds
    elapsed = (uint32_t)chrono::duration_cast<chrono::microseconds>(curTime - startTime).count();
    if(elapsed >= fadeTime) elapsed = fadeTime;
    
    // apply fading
    if(fadeTime) {
      r = map(elapsed, 0, fadeTime, valueSelect.pr, valueSelect.nr); // 16-bit interp
      g = map(elapsed, 0, fadeTime, valueSelect.pg, valueSelect.ng);
      b = map(elapsed, 0, fadeTime, valueSelect.pb, valueSelect.nb);
    } else { // Avoid divide-by-zero in map()
      r = valueSelect.nr;
      g = valueSelect.ng;
      b = valueSelect.nb;
    }

    sendValuesWithThreads(r, g, b);

    if(elapsed >= fadeTime) break;
  }    

  // hold time for color
  for(;;) {
    auto curTime = getTime();

    // get elapsed time in microseconds
    elapsed = (uint32_t)chrono::duration_cast<chrono::microseconds>(curTime - startTime).count();

    sendValuesWithThreads(valueSelect.nr, valueSelect.ng, valueSelect.nb);

    if(elapsed >= totalTime) break;
  }

}

void sceneRunner::sendValuesWithThreads(uint16_t r, uint16_t g, uint16_t b) {
    thread t1(sendToPWN, r, LED_R);
    thread t2(sendToPWN, g, LED_G);
    thread t3(sendToPWN, b, LED_B);

    t1.join();
    t2.join();
    t3.join();
}


void sceneRunner::sendToPWN(uint16_t targetIntensity, int piFacePin) {
    // output driver
    pwmOutput pwm;

    uint16_t finalIntensity = getFinalIntensity(targetIntensity);
    pwm.outputCurrentTimeSlice(finalIntensity, piFacePin);
}

/**
 * Remap 16 bit color intensities to our 0 to 500 PWM driver 
 * range
 */
uint16_t sceneRunner::getFinalIntensity(uint16_t input) {
    uint16_t intensity = map(input, 0, 65535, 0, 500);
    return intensity;
}