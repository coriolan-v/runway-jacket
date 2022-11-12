#include <FastLED.h>
#include "FastLED_RGBW.h"

#define LED_PIN_FRONT     21
#define LED_PIN_SIDES     19
#define LED_PIN_BACK_DATA    4
#define LED_PIN_BACK_CLOCK   5

#define NUM_LEDS_FRONT    30
#define NUM_LEDS_SIDES    17
#define NUM_LEDS_BACK    30
#define BRIGHTNESS  50
int LEDbrightness = BRIGHTNESS;
//#define LED_TYPE_FRONT_SIDES    WS2811
#define COLOR_ORDER GRB
//#define COLOR_ORDER_SIDES RGBW

CRGB ledsFront[NUM_LEDS_FRONT];
CRGB ledsBack[NUM_LEDS_BACK];
CRGBW ledsSide[NUM_LEDS_SIDES];
CRGB *ledsSideRGBW = (CRGB *) &ledsSide[0];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    //delay( 3000 ); // power-up safety delay
    Serial.begin(9600);
     FastLED.addLeds<DOTSTAR, LED_PIN_BACK_DATA, LED_PIN_BACK_CLOCK, GBR>(ledsBack, NUM_LEDS_BACK);
    FastLED.addLeds<WS2811, LED_PIN_FRONT, COLOR_ORDER>(ledsFront, NUM_LEDS_FRONT).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<WS2811, LED_PIN_SIDES, RGB>(ledsSideRGBW, getRGBWsize(NUM_LEDS_SIDES));
   
    
    FastLED.setBrightness(BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
    //checkBrightness();
    //currentPalette = ForestColors_p;           currentBlending = LINEARBLEND; 
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}


unsigned long previousMillis, previousMillisC = 0;
unsigned long previousMillisStartAnim = 0;
void checkBrightness()
{
   if (millis() - previousMillis >= 100) {
    // save the last time you blinked the LED
    previousMillis = millis();

     LEDbrightness = constrain(map(analogRead(A0), 0, 1200, 0, 255), 0, 254);
    //Serial.println(LEDbrightness);

    //int ledBriSides = LEDbrightness - 20;

      //pixels_side.setBrightness(constrain(LEDbrightness, 0, 255));
      //pixels_back.setBrightness(constrain(LEDbrightness, 0, 255));
      //pixels_front.setBrightness(constrain(LEDbrightness, 0, 255));
      //pixels_side.show();
      //FastLED.setBrightness(constrain(LEDbrightness, 0, 255));
      //Serial.println(constrain(LEDbrightness, 0, 255));


  }
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS_FRONT; i++) {
        ledsFront[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
         ledsBack[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }

    for( int i = 0; i < NUM_LEDS_SIDES; i++) {
        //leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
         ledsSide[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
  
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 59;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
       // if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand ==  0)  { currentPalette = PartyColors_p;         currentBlending = LINEARBLEND; }
        //if( secondHand ==  10)  { currentPalette = OceanColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand ==  30)  { currentPalette = LavaColors_p;         currentBlending = LINEARBLEND; }
        //if( secondHand ==  20)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        //if( secondHand ==  25)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        //if( secondHand ==  30)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        //if( secondHand ==  35)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
//        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
//        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
//        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
//        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
//        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
//        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
      //  if( secondHand == 0)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
       // if( secondHand == 10)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
       // if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
       // if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }

    }

    
      // currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; 
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};



// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
