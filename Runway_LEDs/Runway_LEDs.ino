#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define BRIGHTNESS_FRONT 75
#define BRIGHTNESS_BACK 75
#define BRIGHTNESS_SIDES 75

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN_FRONT        21 // On Trinket or Gemma, suggest changing this to 1
#define PIN_SIDES        19
#define PIN_BACK_DATA    4
#define PIN_BACK_CLOCK   5

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS_FRONT 30
#define NUMPIXELS_SIDES 17
#define NUMPIXELS_BACK 30

Adafruit_DotStar pixels_back(NUMPIXELS_BACK, PIN_BACK_DATA, PIN_BACK_CLOCK, DOTSTAR_GBR);
Adafruit_NeoPixel pixels_front(NUMPIXELS_FRONT, PIN_FRONT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_side(NUMPIXELS_SIDES, PIN_SIDES, NEO_GRBW + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  // put your setup code here, to run once:
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  Serial.begin(9600);

  pixels_front.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels_front.show();    
   pixels_front.setBrightness(BRIGHTNESS_FRONT);

   pixels_side.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels_side.show();            // Turn OFF all pixels ASAP
  pixels_side.setBrightness(BRIGHTNESS_SIDES);

  pixels_back.begin(); // Initialize pins for output
  pixels_back.show();  // Turn all LEDs off ASAP
  pixels_back.setBrightness(BRIGHTNESS_BACK);

  clearAll();

  delay(100);

  patternSides();
}

unsigned long previousMillis, previousMillisC = 0;
unsigned long previousMillisStartAnim = 0;
void loop() {
  //patternSides();
  animationBackFront();
  //testAll();
//testFront();
//testSides();
//testBack();

unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 100) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

     int LEDbrightness = map(analogRead(A0), 0, 1200, 0, 255);
    //Serial.println(LEDbrightness);

    int ledBriSides = LEDbrightness - 20;

      pixels_side.setBrightness(constrain(LEDbrightness, 0, 255));
      pixels_back.setBrightness(constrain(LEDbrightness, 0, 255));
      pixels_front.setBrightness(constrain(LEDbrightness, 0, 255));
      pixels_side.show();

      Serial.println(constrain(LEDbrightness, 0, 255));


  }
}

void clearAll(){
  for(int i = 50; i<0; i++){
    pixels_front.setPixelColor(i, pixels_front.Color(0, 0, 0));
    pixels_front.show();
    pixels_back.setPixelColor(i, pixels_back.Color(0, 0, 0));
    pixels_back.show();
    pixels_side.setPixelColor(i, pixels_side.Color(0, 0, 0));
    pixels_side.show();
  }
}

void patternSides(){
  for (int i =0 ; i<NUMPIXELS_SIDES; i++){
    pixels_side.setPixelColor(i, pixels_front.Color(250, 100, 1));
  }
 pixels_side.show();
  
}

void animationBackFront(){
for(int i = 0; i<NUMPIXELS_FRONT+3; i++){
     
     pixels_front.setPixelColor(NUMPIXELS_FRONT-i, pixels_front.Color(255, 0, 0));
     pixels_front.setPixelColor(NUMPIXELS_FRONT-i-1, pixels_front.Color(255, 0, 0));
     pixels_front.setPixelColor(NUMPIXELS_FRONT-i+2, pixels_front.Color(0, 0, 0));
     pixels_front.show();   

     pixels_back.setPixelColor(NUMPIXELS_FRONT-i, pixels_back.Color(255, 0, 0));
     pixels_back.setPixelColor(NUMPIXELS_FRONT-i-1, pixels_back.Color(255, 0, 0));
     pixels_back.setPixelColor(NUMPIXELS_FRONT-i+2, pixels_back.Color(0, 0, 0));
     pixels_back.show();   

    delay(15);
  }
  delay(300);
  
//  for(int i = NUMPIXELS_FRONT; i>=0; i--){
//    // 
//     pixels_front.setPixelColor(i, pixels_front.Color(255, 0, 0));
//    // if(i<NUMPIXELS_FRONT-1) 
//     if(i<NUMPIXELS_FRONT || i ==NUMPIXELS_FRONT) pixels_front.setPixelColor(i+1, pixels_front.Color(0, 0, 0));
//     pixels_front.show();   // Send the updated pixel colors to the hardware.
//
//     //if(i<NUMPIXELS_FRONT)pixels_back.setPixelColor(i+1, pixels_back.Color(0, 0, 0));
//     pixels_back.setPixelColor(i, pixels_back.Color(255, 0, 0));
//     /////if(i<NUMPIXELS_FRONT-1) 
//     if(i<NUMPIXELS_FRONT || i ==NUMPIXELS_FRONT)pixels_back.setPixelColor(i+1, pixels_back.Color(0, 0, 0));
//     pixels_back.show();   // Send the updated pixel colors to the hardware.
//
//    delay(15);
//  }
}

void testAll(){
  for(int i = 0; i< NUMPIXELS_FRONT; i++){
     
     if(i>1) pixels_front.setPixelColor(i-1, pixels_front.Color(0, 0, 0));
     pixels_front.setPixelColor(i, pixels_front.Color(255, 0, 0));
     pixels_front.show();   // Send the updated pixel colors to the hardware.

     
     if(i>1) pixels_side.setPixelColor(i-1, pixels_side.Color(0, 0, 0));
     pixels_side.setPixelColor(i, pixels_side.Color(255, 0, 0));
     pixels_side.show();   // Send the updated pixel colors to the hardware.

     
     if(i>1) pixels_back.setPixelColor(i-1, pixels_back.Color(0, 0, 0));
     pixels_back.setPixelColor(i, pixels_back.Color(255, 0, 0));
     pixels_back.show();   // Send the updated pixel colors to the hardware.
     
     delay(15); // Pause before next pass through loop
  }
}

void testFront(){
    pixels_front.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS_FRONT; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels_front.setPixelColor(i, pixels_front.Color(0, 150, 0));

    pixels_front.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}

void testSides(){
  colorWipe(pixels_side.Color(255,   0,   0)     , 50); // Red
  colorWipe(pixels_side.Color(  0, 255,   0)     , 50); // Green
  colorWipe(pixels_side.Color(  0,   0, 255)     , 50); // Blue
  colorWipe(pixels_side.Color(  0,   0,   0, 255), 50); // True white (not RGB white)
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels_side.numPixels(); i++) { // For each pixel in strip...
    pixels_side.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    pixels_side.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFF0000;      // 'On' color (starts red)

void testBack(){
  pixels_back.setPixelColor(head, color); // 'On' pixel at head
  pixels_back.setPixelColor(tail, 0);     // 'Off' pixel at tail
  pixels_back.show();                     // Refresh strip
  delay(20);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS_BACK) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0xFF0000;             //   Yes, reset to red
  }
  if(++tail >= NUMPIXELS_BACK) tail = 0; // Increment, reset tail index
}
