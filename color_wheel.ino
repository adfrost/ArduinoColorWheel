#include <Adafruit_NeoPixel.h>
#define PIN 1
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.setBrightness(50);  //brightness at 125 is 50%
  strip.show(); // Initialize all pixels to 'off'
}
void loop() {  //Main loop
  colorWipe(strip.Color(101, 255, 101), 100); // White
  rainbowCycle(15);  //color wheel
}
void colorWipe(uint32_t color, uint8_t wait) { //Fill the dots one after the other with a color
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
      strip.show();
      delay(wait);
  }
}
void rainbowCycle(uint8_t wait) {  //display color wheel
  uint16_t i, j;
  for(j=0; j<256*5; j++) { 
    for(i=0; i< strip.numPixels(); i++) { 
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      if(j <= 0) { //wipes white LEDs one at a time instead of all at once
        delay(100);
        strip.show(); 
        }
      }
    strip.show();                
    delay(wait);    
  }                  
}
// Input a value 0 to 255 to get a color value. colors move from r -> g -> b -> back to r.
uint32_t Wheel(byte WheelPos) {  //color wheel
  if(WheelPos < 85) 
      return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);     //r?
  else if(WheelPos < 170) {
      WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);        //g?
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);        //b?
  }
}
