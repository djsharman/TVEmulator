  startTime = millis();
  
  for(;;) {
    elapsed = millis() - startTime;
    if(elapsed >= fadeTime) elapsed = fadeTime;
    if(fadeTime) {
      r = map(elapsed, 0, fadeTime, pr, nr); // 16-bit interp
      g = map(elapsed, 0, fadeTime, pg, ng);
      b = map(elapsed, 0, fadeTime, pb, nb);
    } else { // Avoid divide-by-zero in map()
      r = nr;
      g = ng;
      b = nb;
    }
    for(i=0; i<NUM_LEDS; i++) {
      r8   = r >> 8; // Quantize to 8-bit
      g8   = g >> 8;
      b8   = b >> 8;
      frac = (i << 8) / NUM_LEDS; // LED index scaled to 0-255
      if((r8 < 255) && ((r & 0xFF) >= frac)) r8++; // Boost some fraction
      if((g8 < 255) && ((g & 0xFF) >= frac)) g8++; // of LEDs to handle
      if((b8 < 255) && ((b & 0xFF) >= frac)) b8++; // interp > 8bit
      strip.setPixelColor(i, r8, g8, b8);
    }
    strip.show();
    if(elapsed >= fadeTime) break;
  }
  delay(holdTime);
 
  pr = nr; // Prev RGB = new RGB
  pg = ng;
  pb = nb;